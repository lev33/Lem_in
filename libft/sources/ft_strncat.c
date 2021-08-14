/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:19:44 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/13 12:09:22 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	size_t	i;
	char	*dst;

	dst = dest;
	while (*dest)
		dest++;
	i = 0;
	while (i < nb)
	{
		if (!(*dest++ = *src++))
			return (dst);
		i++;
	}
	*dest = '\0';
	return (dst);
}
