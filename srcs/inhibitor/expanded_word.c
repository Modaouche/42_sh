/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:31:42 by modaouch          #+#    #+#             */
/*   Updated: 2019/09/23 08:48:32 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		backslash(const char *line, char **word, unsigned int *i, int qt)
{
	(void)qt;
	++(*i);
	if (!line[*i])
	{
		*i = 0;
		return (0);
	}
	else if (line[*i] == '\n')
		++(*i);
	else if (ft_strchr(BKSH_DQT_CMP, line[*i]))
		*word = (!*word) ? ft_strndup(line + *i, 1)
			: ft_strjoin_free(*word, ft_strndup(line + *i, 1), 3);
	else if (ft_isspace_inhib(line[*i]))
		*word = (!*word) ? ft_strndup(line + *i, 1)
			: ft_strjoin_free(*word, ft_strndup(line + *i, 1), 3);
	else
		--(*i);
	return (1);
}

int		backslash_end(t_edit *line_e, unsigned int *i, int *ret)
{
	init_line(line_e);
	g_shell.prompt_size = print_prompt(7);
	line_edition(line_e);
	if (!line_e->line)
		line_e->line = ft_memalloc(1);
	if (for_end_word_inhib(line_e->line[0]))
	{
		*i = 0;
		*ret = 0;
		return (0);
	}
	return (1);
}

void	insert_home_path(const char *line, char **word, unsigned int *i)
{
	char			*path;
	unsigned int	x;
	char			*username;

	*i += 1;
	x = 0;
	while (ft_isalnum(line[*i + x]))
		++x;
	if (x == 0)
		path = tild("~");
	else
	{
		username = ft_strsub(line, *i, x);
		path = tild(username);
		ft_strdel(&username);
		*i += x;
	}
	if (path != NULL)
		*word = (!*word) ? ft_strdup(path) : ft_strjoin_free(*word, path, 1);
}

void	insert_env_var_value(const char *line, char **word, unsigned int *i)
{
	unsigned int	x;
	char			*varname;
	char			*value;

	x = 0;
	while (ft_isalnum(line[*i + x]) || line[*i + x] == '_')
		++x;
	varname = x == 0 ? NULL : ft_strsub(line, *i, x);
	if ((value = get_env_value(varname)))
		*word = (!*word) ? value : ft_strjoin_free(*word, value, 3);
	ft_strdel(&varname);
	*i += x;
}

void	expand_brackets(const char *line, char **word, unsigned int *i)
{
	unsigned int	end;
	bool			escape;
	char			*params;
	char			*result;

	*i += 1;
	end = -1;
	escape = 0;
	while (line[*i + ++end])
	{
		if (escape)
		{
			escape = 0;
			continue ;
		}
		if (line[*i + end] == '\\' && (escape = 1))
			continue ;
		if (line[*i + end] == '}')
			break ;
	}
	params = ft_strsub(line, *i, end);
	if ((result = param_expansion(params)) != NULL)
		*word = (!*word) ? result : ft_strjoin_free(*word, result, 3);
	ft_strdel(&params);
	*i += end;
}
