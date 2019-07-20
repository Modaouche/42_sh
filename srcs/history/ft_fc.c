/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araout <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 06:36:44 by araout            #+#    #+#             */
/*   Updated: 2019/07/20 11:23:57 by araout           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "history.h"

/*
** https://www.unix.com/man-page/posix/1p/fc/
*/

int			ft_fc(void *ptr)
{
	char	**args;
	char	**hist;
	int		options;
	int		a;
	int		b;

	args = (char **)ptr;
	if (validate_options(args, "elnrs0123456789") != 0)
	{
		ft_printf_fd(2, "fc: Invalid argument \"%c\"\n",
					validate_options(args, "elnrs"));
		return (1);
	}
	options = get_options(args);
	get_range(args, &a, &b);
	hist = get_history_field(a, b, NULL, (a > b));
	if (get_option(options, 'l'))
		print_history(options, hist, a, b);
	free(hist);
	return (0);
}
