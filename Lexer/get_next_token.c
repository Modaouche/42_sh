/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 08:50:32 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/11 20:39:33 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

/*
t_token    *get_next_token(char **line, int *i)
{
    t_token     *actual_token;
    char         c;

    if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
        return (0);
    if (*line && line[0][*i] != '\n')//pb car si on a un space apres un '\n'// yes confirmed FT_ISSPACE tochange
        skip_predicat(line, i, &ft_isspace);//to change isspace
    actual_token->lexeme = NULL;
    if (!*line || line[0][*i] == '\0')
    {
        actual_token->tokind = T_EOF;
        return (actual_token);
    }
    c = line[0][*i];
    ++(*i);
    if (c == ';')
    {
        actual_token->tokind = T_SEMI;
        actual_token->lexeme = ft_strdup(";");
        return (actual_token);
    }
    else if (c == '\n')
    {
        actual_token->tokind = T_NEWL;
        actual_token->lexeme = ft_strdup("\n");//maybe after to check newl check if the next one is eof('\0')
        return (actual_token);
    }
    else if (c == '&')
    {
        actual_token->tokind = T_AMPER;
        actual_token->lexeme = ft_strdup("&");
        if (line[0][*i] == '&')// && line[0][*i + 1])//mis en commentaire mais je crois que je le gere dans le parser ;) to check
        {
            ++(*i);
            actual_token->tokind = T_AND_IF;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        return (actual_token);
    }
    else if (c == '|')
    {
        actual_token->tokind = T_PIPE;
        actual_token->lexeme = ft_strdup("|");
        if (line[0][*i] == '|')// && line[0][*i + 1])
        {
            ++(*i);
            actual_token->tokind = T_OR_IF;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
        }
        return (actual_token);
    }
    else if (c == '!')
    {
        actual_token->tokind = T_BANG;
        actual_token->lexeme = ft_strdup("!");
        return (actual_token);
    }
    else if (c == '>')
    {
        actual_token->tokind = T_GREAT;
        actual_token->lexeme = ft_strdup(">");
        if (line[0][*i] == '>')
        {
            ++(*i);
            actual_token->tokind = T_DGREAT;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
        }
        else if (line[0][*i] == '&')
        {
            ++(*i);
            actual_token->tokind = T_GREATAND;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        else if (line[0][*i] == '|')
        {
            ++(*i);
            actual_token->tokind = T_CLOBBER;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "|", 1);
        }
        return (actual_token);
    }
    else if (c == '<')
    {
        actual_token->tokind = T_LESS;
        actual_token->lexeme = ft_strdup("<");
        if (line[0][*i] == '<')
        {
            ++(*i);
            actual_token->tokind = T_DLESS;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "<", 1);
            if (line[0][*i] == '-')
            {
                ++(*i);
                actual_token->tokind = T_DLESSDASH;
                actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "-", 1);
            }
        }
        else if (line[0][*i] == '&')
        {
            ++(*i);
            actual_token->tokind = T_LESSAND;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, "&", 1);
        }
        else if (line[0][*i] == '>')
        {
            ++(*i);
            actual_token->tokind = T_LESSGREAT;
            actual_token->lexeme = ft_strjoin_free(actual_token->lexeme, ">", 1);
        }
        return (actual_token);
    }
    else if (token_is_io_nb(c))
    {
        // skip_predicat(line, i, &token_is_io_nb);
        // actual_token->tokind = T_IO_NB;
        // actual_token->lexeme = ft_strndup(&(line[0][*i - 1]), wordlen(&(line[0][*i - 1])));
        // return (actual_token);
    }
    else if (token_isword(c))
    {
        actual_token->tokind = T_WORD;
        actual_token->lexeme = ft_strndup(&(line[0][*i - 1]), wordlen(&(line[0][*i - 1])));
        skip_predicat(line, i, &token_isword);
        return (actual_token);
    }
    actual_token->tokind = T_ERROR;
    return (actual_token);
}
*/

t_token *get_next_token(const char **line, int *i)
{
    t_token     *actual_token;

    if (!(actual_token = (t_token*)ft_memalloc(sizeof(t_token))))
        return (0);
    if (*line && line[0][*i] != '\n')//pb car si on a un space apres un '\n'// yes confirmed FT_ISSPACE tochange
        skip_predicat(line, i, &ft_isspace);
    if (g_token_tab[(size_t)line[0][*i]])
        (*g_token_tab[(size_t)line[0][*i]])(actual_token, *line, i);
    return (actual_token);
}





/*

#ifndef FT_CONV_H
# define FT_CONV_H

# include "ft_printf.h"

t_conv g_convtab[] =
{
	{"c", &ft_char},
	{"s", &ft_string},
	{"p", &ft_pointer},
	{"d", &ft_digit},
	{"D", &ft_digit},
	{"i", &ft_digit},
	{"o", &ft_octal},
	{"x", &ft_hex},
	{"X", &ft_hex_up},
	{"f", &ft_double},
	{"%", &ft_percent},
	{0, NULL}
};

#endif

*/


/*


typedef struct	s_conv
{
	char		*conv;
	void		(*convert)(va_list ap, t_arg *stk);
}				t_conv;


*/

/*
static int		ft_n_precision(const char *format)
{
	if (format[0] == 'n')
		return (1000);
	return (-1);
}

static int		ft_n_conv(const char *fo)
{
	int			n;

	n = 0;
	while (g_convtab[n].conv)
	{
		if (!ft_strncmp(g_convtab[n].conv, fo, ft_strlen(g_convtab[n].conv)))
			return (n);
		n++;
	}
	return (-1);
}

static void		ft_init(t_arg *stk)
{
	stk->i = 0;
	stk->n = 0;
	stk->space = 0;
}

int				ft_printf(const char *format, ...)
{
	va_list		argptr;
	t_arg		stk;

	ft_init(&stk);
	va_start(argptr, format);
	while (format[stk.i])
	{
		if (format[stk.i] == '%')
		{
			stk.n = ft_n_precision(&format[++stk.i]);
			(stk.n > -1) ? ft_space(argptr, &stk) : (void)0;
			stk.n = ft_n_conv(&format[stk.i]);
			(stk.n > -1) ? g_convtab[stk.n].convert(argptr, &stk) : (void)0;
		}
		else
			ft_putchar(format[stk.i++]);
	}
	va_end(argptr);
	return (0);
}

*/
