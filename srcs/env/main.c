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

int		manag_env(char **env, char **arg)
{
	char **env_sh;
	int flag;

	env_sh = env_cpy(env);
	sh_level(&env);
	return (1);// return (exit success)
}


int main(int ac, char **av, char **env)
{
	manag_env(env);
	return (0);
}