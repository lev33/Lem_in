/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:15:58 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/17 12:19:38 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*a;
	char	*b;
	char	*result;

	if (!f || !s ||
				!(result = (char*)ft_memalloc((size_t)ft_strlen((char*)s) + 1)))
		return (NULL);
	a = (char*)s;
	b = result;
	while (*a)
		*b++ = f(*a++);
	return (result);
}
