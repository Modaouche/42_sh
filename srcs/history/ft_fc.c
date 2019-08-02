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


int    exec_by_fc(int options, char **args)
{
  int  i;
  int  nbr;
  
  i = get_argument_starting_index(args, 's');
  if (i = -1)
    
  if (nbr = ft_atoi(args[i]) == 0)
  {
    exec_with_word
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
  if (get_option(option, 's'))
    return (exec_by_fc(options, args));
	hist = get_history_field(a, b, NULL, (a > b));
	if (get_option(options, 'l'))
  {
		print_history(options, hist, a, b);
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
  
  if ((fd = open(tmp_filename, O_RDONLY)) < 0)
    return ;
  while (get_next_line(fd, &line) > 0)
  {
      //TODO: re-exec line
      write_history(line);
      ft_strdel(&line);
  }
  ft_strdel(&line);
  close(fd);
}

void	edit_line(char **lines, char *editor)
{
  char *tmp_filename;
  char *args[3];
  int   fd;
  
  if ((tmp_filename = generate_random_filename()) == NULL)
    return ;
	if (editor == NULL && (editor = get_env_value("FCEDIT") == NULL))
		editor = ft_strdup("/bin/ed");
  if ((fd = open(tmp_filename, O_CREAT, S_IRUSR | S_IWUSR)) < 0)
  {
    ft_strdel(&tmp_filename);
    ft_strdel(&editor);
  }
  while (lines)
  {
    write(fd, *lines, ft_strlen(*lines));
    ++lines;
  } 
  close(fd);
  args[0] = editor;
  args[1] = tmp_filename;
  args[2] = NULL;
  //appel a lexecution
  
  unlink(tmp_filename);
  ft_strdel(&tmp_filename);
  ft_strdel(&editor);
}