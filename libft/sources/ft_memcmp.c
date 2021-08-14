/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:49:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/12 11:18:30 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s11;
	unsigned char *s22;

	s11 = (unsigned char*)s1;
	s22 = (unsigned char*)s2;
	if (n == 0)
		return (0);
	while (*s11 == *s22 && n--)
	{
		s11++;
		s22++;
		if (n == 0)
			return (0);
	}
	return ((int)(*s11 - *s22));
}
