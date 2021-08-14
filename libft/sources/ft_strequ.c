/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:40:16 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/12 13:41:44 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	if (!s1 || !s2)
		return (s1 == s2 ? 1 : 0);
	if (ft_strlen((char*)s1) != ft_strlen((char*)s2))
		return (0);
	while (*s1 && *s2)
	{
		if (*s1++ != *s2++)
			return (0);
	}
	return (1);
}
