/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 07:44:26 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://www.unix.com/man-page/posix/1p/fc/

char    **get_history_field(int a, int b)
{
  char    **ret;
  int      size;
  int      reverse;
  t_list    **head;
  int       i;
  reverse = (a > b);
  if (reverse)
      ft_swap(&a, &b);
  size  = a - b;
  if (!(ret = (char **)ft_memalloc(sizeof((char **) * (size - 1)))))
        return (NULL);
  head = g_shell.history->hist;
  i = 1;
  while (i < a && head)
      head = head->next;
  if (head == NULL)
  {
       close(fd);
        free(ret);
      return (NULL);
  }
  while (i <= b && head)
  {
      ret[a - i] = ((t_hnode *)head->content)->cmd;                    
      head = head->next;
  }
  if (head == NULL)
      ft_memdel((void**)ret);
  close(fd);
  return (ret);
}

int     get_field_size(char **field)
{
  int    i;
  
  i = 0;
  while (field && field[i])
    i++;
  return (i);
  
}

int     print_rev(char **field, int a, int b)
{
    int    i;
  
    i = 0;

      i = get_field_size(field);
      while (--i > 0)
      {
        ft_printf("%d\t%s\n", a, field[i--]);
        if (a > b)
          a--;
        else
          a++;
      }  
    }
    return (1);
}

int     print_field(char *field, int a, int b)
{
  int    i;
  
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

int     print_history(int flag, char **field, int a, int b)
{
    if (get_option(flag, "r") == 1)
      return (print_rev(field, a, b));
    else
      return (print_field(field, a, b));
}

void    get_range(**args, int *a, int *b)
{
  int   i;
  int   flag;
  
  falg = 0;
  i = get_argument_starting_index(args);
  if (i == -1)
  {
    *a = get_hist_size()
    *b = *a - 16;
    return ;
  }
  if (args[i])
    *a = ft_atoi(args[i])
  if (args[++i])
    *b = ft_atoi(args[i])
  else (a <= 0)
  {
    *b = get_hist_size();
    *a = get_hist_size() - *a;
  }
  if (*a == 0)
    *a = get_hist_filesize();
  if (*b == 0)
    *b = get_hist_filesize();
}

int			ft_fc(void *ptr)
{
  char  **tab;
  int   options;
  int   a;
  int   b;
  
  tab = (char **)ptr;
  if (validate_options(tab, "elnrs") != 0)
  {
       ft_printf_fd(2, "fc: Invalid argument \"%c\"\n", validate_options(tab, "elnrs"));
       return (1);
  }
  option = get_options(tab);
  get_range(char **tab, &a, &b);
  if (get_option(option, "l"))
    print_history(option, tab, a, b);
	return (0);
}