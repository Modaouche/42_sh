/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgheraie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 01:12:56 by mgheraie          #+#    #+#             */
/*   Updated: 2019/09/22 01:51:54 by mgheraie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tild.h"
#include <pwd.h>

char	*tild(char *s)
{
	char			*tmp;
	struct passwd	*passwd;

	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 1)
		return ((getpwnam(getlogin()))->pw_dir);
	tmp = s;
	if (!(passwd = getpwnam(tmp)))
		return (NULL);
	if (!(tmp = ft_strdup(passwd->pw_dir)))
		return (NULL);
	return (tmp);
}
