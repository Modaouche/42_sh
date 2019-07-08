/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 22:35:51 by araout            #+#    #+#             */
/*   Updated: 2019/07/08 04:12:21 by araout           ###   ########.fr       */
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
	int		(*f[255])(char **);
}				t_fptr;

char					**set_var_env(char *varname, char *value, char **env);
int						is_var(char *s1, char *s2);
int						find_var(char *varname, char **env);
char					**get_env(char **env);
char					**dump_env(char **env, int size);
void					init_env(char **env);
int						check_perms(char *path);
int						throw_error(char *str, int exec_flag);
int						ft_cd(char **cmd);
int						ft_built_in(char *cmd);
int						print_env(char **s);
int						fexit(char **s);
int						ft_clear(char **s);

# define EXIT 1
# define CLEAN 2

#endif
