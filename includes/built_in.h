/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 11:41:48 by araout            #+#    #+#             */
/*   Updated: 2019/08/30 12:26:46 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H
# include "shell.h"

/*
**	type functions
*/

int					check_built_in(char *args);
int					type_main(void *ptr);
int					check_path(char *args);

/*
**	echo functions
*/
int					ft_echo(void *ptr);

#endif
