/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/07/31 05:13:13 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"
#include <unistd.h>

/*
** https://www.unix.com/man-page/posix/1p/fc/
*/


void  edit_line(char **hist, char *editor);

int    exec_by_fc(int options, char **args)
{
  int  i;
  int  nbr;

  (void)options;
  (void)args;
  return (1);  
  i = get_argument_starting_index(args, 's');
  // if (i == -1)
  if ((nbr = ft_atoi(args[i])) == 0)
  {
      //exec_with_word
  }
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
	if (get_range(args, &a, &b, get_argument_starting_index(args, 'l')) == -1)
		return (-1);
	hist = get_history_field(a, b, NULL, (a > b));
	if (get_option(options, 'l'))
  {
		print_history(options, hist, a, b);
  }
  else if (get_option(options, 's'))
  {
    return (exec_by_fc(options, args));
  }
  else
	{
    edit_line(hist, NULL);
	}
	free(hist);
	return (0);
}

char *generate_random_filename(void)
{
    char n[256];
    unsigned int i;
  
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
      ft_strdel(&g_shell.line_e->line);
      g_shell.line_e->line = line;
      line_parser(g_shell.line_e);
      line_execution();
      write_history(line);
  }
  //ft_strdel(&line);
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
      while (*hist)
      {
        write(fd, *hist, ft_strlen(*hist));
        write(fd, "\n", 1);
        ++hist;
      } 
      close(fd);
  }
  return (filename);
}

void	edit_line(char **hist, char *editor)
{
  char *tmp_filename;
  char *args[3];
  int   fd;
  
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
  fd = fork();
  if (fd == 0)
  {
    execve(editor, args, g_shell.envp);
    ft_printf_fd(2, "fc: Error, could execute %s for some reason.\n", editor);
    fexit(NULL);
  }
  else
  {
      if (fd == -1)
        ft_printf_fd(2, "fc: Error, not enough ressources to fork.\n");
      else
      {
        waitpid(fd, NULL, P_PID);
        exec_file(tmp_filename);
      }
  }
  unlink(tmp_filename);
  ft_strdel(&tmp_filename);
  ft_strdel(&editor);
}