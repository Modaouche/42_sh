/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 02:14:05 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 09:39:52 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static char		*generate_random_filename(void)
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

static char		*generate_tmp_hist_file(char **hist, int tries, char *f, int fd)
{
	if ((f = generate_random_filename()) == NULL)
		return (NULL);
	fd = open(f, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	while (fd < 0 && tries++ < 3)
	{
		ft_strdel(&f);
		if ((f = generate_random_filename()) == NULL)
			return (NULL);
		fd = open(f, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	}
	if (fd < 0)
		ft_strdel(&f);
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
	return (f);
}

static int		edit_line_2(char **args, char **editor, char **hist, char **t)
{
	int		flag;

	flag = 0;
	errno = 0;
	if (*editor == NULL && (*editor = get_env_value("FCEDIT")) == NULL)
	{
		*editor = ft_strdup("/bin/ed");
		flag = 1;
	}
	if (*editor == NULL \
			|| (*t = generate_tmp_hist_file(hist, 0, NULL, 0)) == NULL)
	{
		ft_strdel(editor);
		return (flag);
	}
	args[0] = *editor;
	args[1] = *t;
	args[2] = NULL;
	return (flag);
}

void			fork_fc_edit(char *tmp_filename, char **args, char *editor)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (tcsetattr(STDERR_FILENO, TCSADRAIN, g_shell.termiold) == -1)
			le_exit(0);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, g_shell.termiold) == -1)
			le_exit(0);
		execve(editor, args, g_shell.envp);
		ft_printf_fd(2, "fc: Error, could not execute %s .\n", editor);
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
}

void			edit_line(char **hist, char *editor)
{
	char	*tmp_filename;
	char	*args[3];
	int		flag_free_ed;

	flag_free_ed = edit_line_2((char **)&args, &editor, hist, &tmp_filename);
	fork_fc_edit(tmp_filename, args, editor);
	unlink(tmp_filename);
	ft_strdel(&tmp_filename);
	if (flag_free_ed)
		ft_strdel(&editor);
	ft_printf("Errno = %d\n", errno);
}
