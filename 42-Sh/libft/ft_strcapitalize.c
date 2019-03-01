/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modaouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 19:04:14 by modaouch          #+#    #+#             */
/*   Updated: 2018/06/23 20:22:00 by modaouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	i = 0;
	if (str[i] >= 'a' && str[i] <= 'z')
		str[i] = str[i] - 32;
	i++;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') &&
				(!((str[i - 1] >= 'a' && str[i - 1] <= 'z') ||
				(str[i - 1] >= 'A' && str[i - 1] <= 'Z') ||
				(str[i - 1] >= '0' && str[i - 1] <= '9'))))
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}
