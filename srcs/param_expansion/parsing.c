/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 23:45:48 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/23 09:34:04 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "param_expansion.h"

void		check_diez(char c, char *arg, uint16_t *signe)
{
	size_t i;

	if (arg[0] == c)
		*signe |= LENGTH;
	i = (*signe & LENGTH) ? 0 : -1;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] == ':')
	{
		*signe |= PARAMUNSET;
		i++;
	}
	if (!arg[i] && *signe & LENGTH)
		return ;
	if (arg[i] == '#')
	{
		(*signe & LENGTH) ? *signe = UIERROR : 0;
		*signe |= ONEDIEZ;
		i++;
	}
	if (arg[i] == '#')
	{
		(*signe & ONEDIEZ) ? *signe ^= ONEDIEZ : 0;
		*signe |= DOUBLDIEZ;
	}
}

void		check_percent(char c, char *arg, uint16_t *signe)
{
	size_t i;

	i = 0;
	if (arg[0] == c)
		*signe = UIERROR;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] == ':')
	{
		*signe |= PARAMUNSET;
		i++;
	}
	if (arg[i] == '%')
	{
		*signe |= ONEPER;
		i++;
	}
	if (arg[i] == '%')
	{
		(*signe & ONEPER) ? *signe ^= ONEPER : 0;
		*signe |= DOUBLPER;
	}
}

void		check_default(char c, char *arg, uint16_t flag, uint16_t *signe)
{
	size_t i;

	i = 0;
	if (arg[0] == c)
		*signe = UIERROR;
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (arg[i] == ':')
	{
		*signe |= PARAMUNSET;
		i++;
	}
	if (arg[i] == c)
	{
		*signe |= flag;
		i++;
	}
}

void		check_flag(char *arg, uint16_t *signe, int i)
{
	char c;

	c = arg[i];
	(c == '-') ? check_default(c, arg, PARAMDEFAULT, signe) : 0;
	(c == '=') ? check_default(c, arg, PARAMASSIGN, signe) : 0;
	(c == '?') ? check_default(c, arg, PARAMERROR, signe) : 0;
	(c == '+') ? check_default(c, arg, PARAMALTERNATIVE, signe) : 0;
	(c == '#') ? check_diez(c, arg, signe) : 0;
	(c == '%') ? check_percent(c, arg, signe) : 0;
}

char		check_activeflag(uint16_t signe)
{
	size_t		checksub;
	uint16_t	oct;

	checksub = 0;
	oct = 1;
	while (oct <= 512)
	{
		if (signe & PARAMUNSET)
		{
			if (signe & LENGTH || signe & ONEPER || signe & DOUBLPER
					|| signe & ONEDIEZ || signe & DOUBLDIEZ)
				return (0);
			oct = oct << 1;
		}
		if (oct & signe)
			checksub++;
		oct = oct << 1;
	}
	if (checksub > 1)
		return (0);
	return (1);
}
