/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:42:58 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/12 12:49:32 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = (0);
	while (*s)
	{
		if (*s == c)
			last = (char*)s;
		s++;
	}
	if (last)
		return (last);
	if (c == '\0')
		return ((char*)s);
	return (0);
}
