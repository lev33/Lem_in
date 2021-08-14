/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 20:35:11 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/05/21 20:38:39 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_isint(char *str)
{
	unsigned int	res;
	unsigned int	lim;
	int				i;
	int				sign;
	int				digits;

	res = 0;
	digits = 0;
	lim = (unsigned int)((int)((unsigned)(~0L) >> 1) / 10);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && ++digits)
	{
		if (((res > lim || (res == lim && (str[i] - '0') > 7))
					&& sign == 1)
				|| ((res > lim || (res == lim && (str[i] - '0') > 8))
					&& sign == -1))
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return (!str[i] && digits);
}
