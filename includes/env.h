/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 22:35:51 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 12:20:07 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include <sys/stat.h>
# include "shell.h"

typedef struct s_edit	t_edit;

char					**set_var_env(char *varname, char *value, char **env);
int						is_var(char *s1, char *s2);
int						find_var_idx(char *varname, char **env);
char					**get_env(char **env);
char					**dump_env(char **env, int size);
void					init_env(char **env);
int						check_perms(char *path);
int						throw_error(char *str, int exec_flag);
int						ft_cd(char **ptr);
int						ft_built_in(char **cmd);
int						print_env(char **ptr);
int						fexit(char **ptr);
int						ft_clear(char **ptr);
int						ft_pwd(char **ptr);
void					cd_set_env(int exec_flag, char *pwd);
int						ft_setenv(char **args);
int						ft_unsetenv(char *cmd);
int						ft_unsetenv_cmd(char **ptr);
void					free_env(int a);
void					free_tmp(char **s);
int						ft_setenv_equal(char *cmd, int flag);
char					*get_env_value(char *varname);

# define EXIT 1
# define CLEAN 2

#endif
