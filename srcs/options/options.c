/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:03:29 by modaouch          #+#    #+#             */
/*   Updated: 2019/05/14 01:48:52 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**  validate_options
**
**  - Returns 0 if the options contained in args match the valid options
**    Otherwise, returns the first occurence (ascii char) of a wrong option
*/

char	validate_options(char **args, char *valid_options)
{
	unsigned int i;
	unsigned int options;
	unsigned int x;

	options = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '-')
		{
			++i;
			continue ;
		}
		if (ft_strcmp(args[i], "--") == 0)
			return (0);
		x = 1;
		while (args[i][x])
		{
			if (ft_cfind(valid_options, args[i][x]) == -1)
				return (args[i][x]);
			++x;
		}
		++i;
	}
	return (0);
}

/*
**  get_options
**
**  - Returns an integer with the bits 0 to 25 being set based on a-z
**    Uppercase are ignored.
*/

int		get_options(char **args)
{
	unsigned int i;
	unsigned int options;
	unsigned int x;

	options = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '-')
		{
			++i;
			continue ;
		}
		if (ft_strcmp(args[i], "--") == 0)
			break ;
		x = 1;
		while (args[i][x])
		{
			if (ft_isascii(args[i][x]))
				options |= (1 << (ft_tolower(args[i][x]) - 'a'));
			++x;
		}
		++i;
	}
	return (options);
}

/*
**  get_option
**
**  - Returns 1 if the given letter is contained within the variable
**    Returns 0 otherwise
*/

int		get_option(int options, char letter)
{
	return ((options >> (letter - 'a')) & 1);
}
