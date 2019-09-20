/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:41:48 by araout            #+#    #+#             */
/*   Updated: 2019/09/09 23:20:35 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "shell.h"

#define BUILTIN_LIST "cd set clear pwd export unset history fc echo type "\
					 "alias unalias test exit jobs fg bg"

/*
**	type functions
*/

int					check_built_in(char *args);
int					type_main(char **args);
int					check_path(char *args);
int					check_path_abs(char *args);
int					check_alias(char *args);

/*
**	echo functions
*/
int					ft_echo(char **args);

/*
**	echo functions
*/
int					ft_jobs(char **args);
int					ft_fg(char **args);
int					ft_bg(char **args);

/*
**  ft_test
*/
int					ft_test_main(char **args);

/*
** alias functions
*/
char				*concat_alias_string(char *name, char *value);
void				set_alias_value(char *name, char *value);
char				**copy_alias_tab(char **array, char *newelem);
int					remove_alias(char *name);
char				*get_alias_value(char *name);
int					ft_alias(char **args);
int					ft_unalias(char **args);

#endif
