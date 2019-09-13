/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 09:14:49 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"
#include <unistd.h>

/*
** https://www.unix.com/man-page/posix/1p/fc/
*/

int				check_args_nbr(int options, char **args, int *a)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		*a = get_hist_nbline();
	if (get_option(options, 'e'))
	{
		if (i == 2)
		{
			ft_putstr_fd("42sh: fc: -e: options requires an argument\n", 2);
			return (-1);
		}
		else if (i > 4)
			return (1);
		else
			return (0);
	}
	else if (i <= 2)
		return (0);
	else
		return (1);
}

static int			ft_fc_2(t_fc *fc_struct)
{
	free(fc_struct->hist);
	if (check_args_nbr(fc_struct->options,\
				fc_struct->args, &fc_struct->a) == -1)
		return (0);
	else if (check_args_nbr(fc_struct->options, fc_struct->args,\
				&fc_struct->a) > 0)
		fc_struct->hist = get_history_field(fc_struct->a,\
				fc_struct->b, NULL, 1);
	else
		fc_struct->hist = get_history_field(fc_struct->a,\
				fc_struct->a, NULL, 1);
	if (get_option(fc_struct->options, 'e'))
		edit_line(fc_struct->hist, fc_struct->args[get_argument_starting_index(fc_struct->args, 'e')]);
	else
		edit_line(fc_struct->hist, NULL);
	return (1);
}

t_fc			*build_struct_fc(char **args)
{
	t_fc		*fc_struct;

	if (validate_options(args, "elnrs0123456789") != 0)
	{
		ft_printf_fd(2, "fc: Invalid argument \"%c\"\n",
				validate_options(args, "elnrs"));
		return (NULL);
	}
	if (!(fc_struct = (t_fc *)malloc(sizeof(t_fc))))
		return (NULL);
	fc_struct->args = args;
	fc_struct->options = get_options(args);
	fc_struct->a = 0;
	fc_struct->b = 0;
	fc_struct->hist = NULL;
	return (fc_struct);
}

int				ft_fc(void *ptr)
{
	char	**args;
	t_fc	*fc_struct;

	args = (char **)ptr;
	if ((fc_struct = build_struct_fc(args)) == NULL)
		return (-1);
	if (get_option(fc_struct->options, 's') && (free_fc(fc_struct) == -1))
		return (exec_fc_s(args, NULL, 0));
	if (get_range(args, &fc_struct->a, &fc_struct->b,
				get_argument_starting_index(args, 'l')\
				+ get_option(fc_struct->options, 'e')) == -1)
		return (free_fc(fc_struct));
	fc_struct->hist = get_history_field(fc_struct->a, fc_struct->b, NULL,\
			(fc_struct->a > fc_struct->b));
	if (get_option(fc_struct->options, 'l'))
		print_history(fc_struct->options, fc_struct->hist,\
				fc_struct->a, fc_struct->b);
	else
		ft_fc_2(fc_struct);
	free_fc(fc_struct);
	return (1);
}

void			exec_file(char *filename)
{
	int			fd;
	char		*line;

	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, "fc: Error, could not execute modified history.\n");
		return ;
	}
	while (get_next_line(fd, &line) > 0)
	{
		ft_printf("Executing [%s]\n", line);
		init_line(g_shell.line_e);
		g_shell.line_e->line = line;
		line_parser(g_shell.line_e);
		line_execution();
		write_history(line);
	}
//	ft_strdel(&line);
	g_shell.isnt_interactive = 1;
	close(fd);
}
