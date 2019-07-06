#include "env.h"

/*
**  Check if the value exist and return his index
*/
int			check_env_value(char **env, char *to_check)
{
	int c;

	if (env)
	{
		c = 0;
		while (env[c])
		{
			if (ft_strnstr(env[c], to_check, ft_cfind(env[c], '=')))
				return (c);
			c++;
		}
	}
	return (-1);
}