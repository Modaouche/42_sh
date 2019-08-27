/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/08/27 11:35:28 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"
#include <unistd.h>

/*
 ** https://www.unix.com/man-page/posix/1p/fc/
 */


void	edit_line(char **hist, char *editor);

int		get_index_fc_by_string(char *arg)
{
	int		i;
	t_list	*head;
	int		index;

	index = -1;
	i = 1;
	head = g_shell.history->hist;
	if (!arg)
		return (get_hist_nbline());
	while ((head = head->next) != NULL)
	{
		i++;
		if (!ft_strncmp(((t_hnode *)head->content)->cmd, arg, ft_strlen(arg)))
			index = i;
	}
	return (index);
}

char	*get_line_to_exec(int index)
{
	t_list	*head;
	int		i;

	i = 1;
	head = g_shell.history->hist;
	if (i == index)
		return (((t_hnode *)head->content)->cmd);
	while (head->next)
	{
		if (i == index)
			return (((t_hnode *)head->content)->cmd);
		i++;
		head = head->next;
	}
	return (((t_hnode *)head->content)->cmd);
}

int		exec_fc_s(int options, char **args)
{
	int		i;
	int		index;
	char	*line;

	(void)options;
	i = get_argument_starting_index(args, 's');
	if (i == -1)
		index = get_hist_nbline() + 1;
	else if (ft_isdigit(*(args[i])) || *(args[i]) == '-' || *(args[i]) == '+')
	{
		index = ft_atoi(args[i]);
		set_a_b_under_zero(&index, &index);
	}
	else
	{
		index = get_index_fc_by_string(args[i]);
		if (index == -1)
			ft_putstr_fd("42sh: fc: no command found", 2);
	}
	line =  ft_strdup(get_line_to_exec(index));
	init_line(g_shell.line_e);
	g_shell.line_e->line = line;
	line_parser(g_shell.line_e);
	line_execution();
	return (1);
}

int			check_args_nbr(int options, char **args, int *a)
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
	if (get_option(options, 's'))
		return (exec_fc_s(options, args));
	if (get_range(args, &a, &b, get_argument_starting_index(args, 'l')\
				+ get_option(options, 'e')) == -1)
		return (-1);
	hist = get_history_field(a, b, NULL, (a > b));
	if (get_option(options, 'l'))
		print_history(options, hist, a, b);
	else
	{
		free(hist);
		if (check_args_nbr(options, args, &a) == -1)
			return (0);
		else if (check_args_nbr(options, args, &a) > 0)
			hist = get_history_field(a, b, NULL, 1);
		else
			hist = get_history_field(a, a, NULL, 1);
		if (get_option(options, 'e'))
			edit_line(hist, args[get_argument_starting_index(args, 'e')]);
		else
			edit_line(hist, NULL);
	}
	free(hist);
	return (1);
}

char *generate_random_filename(void)
{
	char			n[256];
	unsigned int	i;

	i = 0;
	ft_strcpy(n, "/tmp/fc42_0");
	while (access(n, F_OK) != -1)
	{
		ft_itoa_str(i, n + 10, 250);
		if (++i == 0)
			return (NULL);
	}
	return (ft_strdup(n));
}

void  exec_file(char *filename)
{
	int   fd;
	char   *line;

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
	//ft_strdel(&line);
	g_shell.isnt_interactive = 1;
	close(fd);
}

char *generate_tmp_hist_file(char **hist)
{
	char *filename;
	int tries;
	int fd;

	if ((filename = generate_random_filename()) == NULL)
		return (NULL);
	fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	tries = 0;
	while (fd < 0 && tries++ < 3)
	{
		ft_strdel(&filename);
		if ((filename = generate_random_filename()) == NULL)
			return (NULL);
		fd = open(filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	}
	if (fd < 0)
		ft_strdel(&filename);
	else
	{
		while (hist && *hist)
		{
			write(fd, *hist, ft_strlen(*hist));
			write(fd, "\n", 1);
			++hist;
		} 
		//close(fd);
	}
	close(fd);
	return (filename);
}

void	edit_line(char **hist, char *editor)
{
	char	*tmp_filename;
	char	*args[3];
	int	pid;

	errno = 0;
	if (editor == NULL && (editor = get_env_value("FCEDIT")) == NULL)
		editor = ft_strdup("/bin/ed");
	if (editor == NULL || (tmp_filename = generate_tmp_hist_file(hist)) == NULL)
	{
		ft_strdel(&editor);
		return ;
	}
	args[0] = editor;
	args[1] = tmp_filename;
	args[2] = NULL;
	ft_printf("Errno = %d\n", errno);
	pid = fork();
	if (pid == 0)
	{
		if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
			toexit(0, "tcsetattr", 1);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, g_shell.termiold) == -1)
			toexit(0, "tcsetattr", 1);
		execve(editor, args, g_shell.envp);
		ft_printf_fd(2, "fc: Error, could execute %s for some reason.\n", editor);
		fexit(NULL);
	}
	else
	{
		if (pid == -1)
			ft_printf_fd(2, "fc: Error, not enough ressources to fork.\n");
		else
		{
			waitpid(pid, NULL, 0);
			exec_file(tmp_filename);
		}
	}
	unlink(tmp_filename);
	ft_strdel(&tmp_filename);
	ft_strdel(&editor);
	ft_printf("Errno = %d\n", errno);
}
