/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kicausse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 07:09:22 by kicausse          #+#    #+#             */
/*   Updated: 2019/04/25 20:14:19 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void					ft_list_delete(t_list **list)
{
	t_list *tmp;

	if (list == NULL)
		return ;
	while (*list != NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		ft_strdel(&tmp->content);
		free(tmp);
	} 
}
