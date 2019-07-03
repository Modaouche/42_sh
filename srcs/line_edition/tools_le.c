/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_le.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 11:00:19 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 02:28:51 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     is_arrow(char *key)
{
    return ((key[0] == 27 && key[1] == 91 && (key[2] >= 65) && key[2] <= 68)\
    ? key[2] : 0);
}

void    cursor_reposition(size_t n)
{
    while (n)
    {
        tputs(tgetstr("le", NULL), 1, ft_puti);
        n--;
    }
}

void        ft_nlcr(void)
{
    tputs(tgetstr("do", NULL), 1, ft_puti);
    tputs(tgetstr("cr", NULL), 1, ft_puti);
}

uint         get_line_height(t_edit *line_e, unsigned int end)
{
    unsigned int i;
    unsigned int x;
    unsigned int height;

    if (line_e->line == NULL)
        return (0);
    i = 0;
    x = line_e->prompt_size;
    height = 1;
    while (i < end && line_e->line[i])
    {
        ++x;
        if (line_e->line[i] == '\t')
            x += TAB_LEN - 1;
        if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
        {
            x = 0;
            ++height;
        }
    }
    return (height);
}

uint         get_index_x_pos(t_edit *line_e, unsigned int pos)
{
    unsigned int i;
    unsigned int x;
    unsigned int n;

    if (line_e->line == NULL)
        return (0);
    i = 0;
    x = line_e->prompt_size;
    n = 0;
    while (i < pos && line_e->line[i])
    {
        if (line_e->line[i] == '\t')
            x += TAB_LEN - 1;
        if (x++ >= line_e->winsize_col)
            ++n;
        if (line_e->line[i++] == '\n' || x >= line_e->winsize_col)
            x = 0;
    }
    return (x + n);
}

size_t		print_prompt(unsigned int btn)
{
    char	*prompt;
    size_t	len;

    if (btn == 0)
        prompt = ft_strdup("42sh (current path) 12$> ");//ajout du path soon
    else if (btn == 1)
	    prompt = ft_strdup("pipe $> ");
    else if (btn == 2)
	    prompt = ft_strdup("cmdor $> ");
    else if (btn == 3)
	    prompt = ft_strdup("cmdand $> ");
    else if (btn == 4)
	    prompt = ft_strdup("quote $> ");
    else if (btn == 5)
	    prompt = ft_strdup("dquote $> ");
    else if (btn == 6)
	    prompt = ft_strdup("heredoc $> ");
    else if (btn == 7)
	    prompt = ft_strdup("$> ");
//    else if (btn == 6)
//	    prompt = ft_strdup("bquote $> ");//not sure
    len = ft_strlen(prompt);
    ft_putstr(prompt);
    ft_strdel(&prompt);
    return (len);
}

int             ft_puti(int i)
{
	return (write(STDERR_FILENO, &i, 1));
}
