#include "env.h"

char 		**create_env_loc(char **env)
{
	char **env_glo;
	int i;

	if (!(env_glo = (char **)ft_memalloc(sizeof(char *) * (ft_tablen(env) + 1))))
		return (NULL);
	i = -1;
	while (env[++i])
		env_glo[i] = env[i];
	env_glo[i] = 0;
	return (env_glo);
}

int		manag_env(char **env, char **arg)
{
	char **env_sh;
	char **env_glo;
	int flag;

	env_sh = env_cpy(env);
	print_env(env_sh);
	env_glo = create_env_loc(env);
	print_env(env_glo);
	return (1);// return (exit success)
}


int main(int ac, char **av, char **env)
{
	manag_env(env, av);
	return (0);
}