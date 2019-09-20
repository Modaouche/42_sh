//
// Created by Gheraieb Mohamed on 2019-07-09.
//

#include "libft.h"


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
			if (!(res = ft_strjoin_free(&res, &tmp)))
				return (NULL);
		}
		i++;
	}
	va_end(ap);
	return (res);
}
