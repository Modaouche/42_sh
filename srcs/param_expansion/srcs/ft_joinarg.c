//
// Created by Gheraieb Mohamed on 2019-07-09.
//

#include "libft.h"

#include <unistd.h>
#include <stdlib.h>


#include <stdarg.h>

char	*ft_strjoin_free2(char **s1, char **s2)
{
	char	*str;
	size_t	size;

	if (!s1 || !s2)
		return ((str = ft_strdup("")));
	size = ft_strlen(*s1) + ft_strlen(*s2);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	if (str)
		ft_memset(str, '\0', size + 1);
	ft_strcat(str, *s1);
	free(*s1);
	ft_strcat(str, *s2);
	free(*s2);
	return (str);
}

char    *ft_joinarg(size_t nbelem, ...)
{
	va_list ap;
	char    *res;
	char    *tmp;
	size_t  i;

	va_start(ap, nbelem);
	i = 0;
	while (i < nbelem)
	{
		if (!(tmp = ft_strdup(va_arg(ap, char*))))
			return (NULL);
		if (i == 0)
		{
			if (!(res = ft_strdup(tmp)))
				return (NULL);
			ft_strdel(&tmp);
		}
		else
		{
			if (!(res = ft_strjoin_free2(&res, &tmp)))
				return (NULL);
		}
		i++;
	}
	va_end(ap);
	return (res);
}
