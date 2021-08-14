/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 15:08:51 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/17 10:46:10 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	if (src != dst)
	{
		a = (unsigned char*)src;
		b = (unsigned char*)dst;
		while (n--)
			*b++ = *a++;
	}
	return (dst);
}
