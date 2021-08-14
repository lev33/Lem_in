/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:42:24 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/17 10:44:53 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *a;
	unsigned char *b;

	if (src != dst)
	{
		a = (unsigned char*)src;
		b = (unsigned char*)dst;
		if (a < b)
			while (len--)
				b[len] = a[len];
		else
			while (len--)
				*b++ = *a++;
	}
	return (dst);
}
