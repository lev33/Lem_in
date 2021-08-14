/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:25:07 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/12 16:24:51 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
							int c, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)src;
	b = (unsigned char*)dst;
	while (n--)
	{
		*b = *a;
		if (*a == (unsigned char)c)
			return ((void*)b + 1);
		a++;
		b++;
	}
	return (NULL);
}
