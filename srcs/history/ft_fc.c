/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/07/19 05:34:41 by kicausse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"

//https://www.unix.com/man-page/posix/1p/fc/

char		**get_history_field(int a, int b)
{
	char	**ret;
	int		size;
	int		reverse;
	t_list	*head;
	int		i;

	reverse = (a > b);
	if (reverse)
		ft_swap_int(&a, &b);
	size = b - a;
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * (size + 2))))
		return (NULL);
	head = g_shell.history->hist;
	i = 1;
	while (i < a && head)
	{
		head = head->next;
		++i;
	}
	if (head == NULL)
	{
		free(ret);
		return (NULL);
	}
	while (i <= b && head)
	{
		ret[i - a] = ((t_hnode *)head->content)->cmd;
		head = head->next;
		++i;
	}
	if (head == NULL)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

int			get_field_size(char **field)
{
	int		i;

	i = 0;
	while (field && field[i])
		i++;
	return (i);
}

void		print_rev(char **field, int a, int b)
{
	int		i;

	i = get_field_size(field);
	while (--i >= 0)
	{
		ft_printf("%d\t%s\n", a, field[i]);
		if (a > b)
			--a;
		else
			++a;
	}
}

void		print_field(char **field, int a, int b)
{
	int		i;

	i = 0;
	while (field[i])
	{
		if (a > b)
			ft_printf("%d\t", a--);
		else
			ft_printf("%d\t", a++);
		ft_printf("%s\n", field[i++]);
	}
}

int			print_history(int flag, char **field, int a, int b)
{
	if (field == NULL)
		return (0);
	if (get_option(flag, 'r') == 1)
		print_rev(field, a, b);
	else
		print_field(field, a, b);
	return (1);
}

void		get_range(char **args, int *a, int *b)
{
	int		i;
	int		flag;

	flag = 0;
	i = get_argument_starting_index(args, 'l');
	*b = 0;
	if (i == -1)
	{
		*b = get_hist_nbline();
		*a = *b - 16;
		return ;
	}
	if (args[i])
		*a = ft_atoi(args[i]);
	if (args[++i])
		*b = ft_atoi(args[i]);
	else if (*a <= 0)
	{
		if (*a == 0)
			*a = -1;
		*b = get_hist_nbline();
		*a = *b + *a + 1;
	}
	if (*a == 0 || *a == -1)
		*a = get_hist_nbline();
	if (*b == 0 || *b == -1)
		*b = get_hist_nbline();
}

int			ft_fc(void *ptr)
{
	char	**args;
	char	**hist;
	int		options;
	int		a;
	int		b;

	args = (char **)ptr;
	if (validate_options(args, "elnrs0123456789") != 0)
	{
		ft_printf_fd(2, "fc: Invalid argument \"%c\"\n",
					validate_options(args, "elnrs"));
		return (1);
	}
	options = get_options(args);
	get_range(args, &a, &b);
	hist = get_history_field(a, b);
	if (get_option(options, 'l'))
		print_history(options, hist, a, b);
	return (0);
}
