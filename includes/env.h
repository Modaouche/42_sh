/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 22:35:51 by araout            #+#    #+#             */
/*   Updated: 2019/07/18 03:06:41 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <sys/stat.h>
# include "shell.h"

typedef struct s_edit	t_edit;

typedef struct			s_fptr
{
	char	**flag;
	int		(*f[255])(void *);
}						t_fptr;

char					**set_var_env(char *varname, char *value, char **env);
int						is_var(char *s1, char *s2);
int						find_var(char *varname, char **env);
char					**get_env(char **env);
char					**dump_env(char **env, int size);
void					init_env(char **env);
int						check_perms(char *path);
int						throw_error(char *str, int exec_flag);
int						ft_cd(void *ptr);
int						ft_built_in(char *cmd);
int						print_env(void *ptr);
int						fexit(void *ptr);
int						ft_clear(void *ptr);
int						ft_pwd(void *ptr);
void					cd_set_env(int exec_flag, char *pwd);
int						ft_setenv(void *ptr);
int						ft_unsetenv(void *ptr);
int						ft_unsetenv_cmd(void *ptr);
void					free_env();
int						ft_setenv_equal(char *cmd, int flag);
char					*get_env_value(char *varname);
int						ft_history(void *ptr);

# define EXIT 1
# define CLEAN 2

#endif
