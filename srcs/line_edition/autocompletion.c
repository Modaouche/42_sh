/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 04:46:11 by kicausse          #+#    #+#             */
/*   Updated: 2019/09/23 09:14:47 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

void	replace_line_raw(t_edit *line_e, char *str)
{
	cursor_start(line_e);
	ft_strdel(&line_e->line);
	line_e->line = str;
	line_e->len = ft_strlen(str);
	line_e->cursor_pos = line_e->len;
	print_line(line_e, 0);
}

void	replace_word(t_edit *line_e, char *new, size_t length, char *suffix)
{
	char			*str;

	if (line_e->autocomp_quote == 2)
		new = escape_singlequote(new, length);
	else if (line_e->autocomp_quote == 1)
		new = escape_name(new, AUTOCOMP_ESCAPED_CHARS_IN_DBLQUOTE, length);
	else
		new = escape_name(new, AUTOCOMP_ESCAPED_CHARS, length);
	if ((length = ft_strlen(new)) == 0)
		return ;
	if (!(str = ft_strnew(line_e->autocomp_point + length + ft_strlen(suffix)
					+ (line_e->autocomp_quote > 0))))
	{
		ft_strdel(&new);
		return ;
	}
	ft_memcpy(str, line_e->line, line_e->autocomp_point);
	ft_memcpy(str + line_e->autocomp_point, new, length);
	ft_strcat(str + line_e->autocomp_point + length, suffix);
	if (line_e->autocomp_quote == 1 && length != 0)
		ft_strcat(str + line_e->autocomp_point + length, "\"");
	else if (line_e->autocomp_quote == 2 && length != 0)
		ft_strcat(str + line_e->autocomp_point + length, "'");
	ft_strdel(&new);
	replace_line_raw(line_e, str);
}

void	replace_word_from_completion(t_edit *line_e)
{
	t_file			*file;

	file = ft_file_list_at(line_e->autocomp_list, line_e->autocomp_idx);
	if (file == NULL)
		return ;
	if (line_e->autocomp_size == 1 && (file->type == AUTOCOMP_TYPE_FOLDER
				|| file->type == AUTOCOMP_TYPE_FOLDER2))
		replace_word(line_e, file->name, ft_strlen(file->name), "/");
	else
		replace_word(line_e, file->name, ft_strlen(file->name), NULL);
}

char	*escape_singlequote(char *name, unsigned int max)
{
	unsigned int	x;
	unsigned int	i;
	char			*new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
		if (++x && name[i++] == '\'')
			x += 3;
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	while (*name && max-- != 0)
	{
		if (*name == '\'')
		{
			ft_memcpy(new + x, (char[]){0x27, 0x5c, 0x27, 0x27}, 4);
			x += 4;
		}
		else
			new[x++] = *name;
		++name;
	}
	return (new);
}

char	*escape_name(char *name, char *escaped_chars, unsigned int max)
{
	unsigned int	x;
	unsigned int	i;
	char			*new;

	i = 0;
	x = 0;
	while (name[i] && i < max)
	{
		if (ft_cfind(escaped_chars, name[i++]) != -1)
			++x;
		++x;
	}
	if ((new = ft_strnew(x)) == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (name[i] && i < max)
	{
		if (ft_cfind(escaped_chars, name[i]) != -1)
			new[x++] = '\\';
		new[x++] = name[i++];
	}
	return (new);
}
