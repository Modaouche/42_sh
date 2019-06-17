#include "env.h"

int			check_env_value(char **env, char *to_check)
{
	int c;

	if (env)
	{
		c = 0;
		while (env[c])
		{
			if (ft_strnstr(env[i], to_check, ft_cfind(env[i], '='))
				return (c);
			c++;
		}
	}
	return (0);
}
