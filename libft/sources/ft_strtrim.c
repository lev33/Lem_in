/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:47:38 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/13 11:40:42 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	char	*str;
	char	*trm;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && (j >= 0))
		j--;
	if (i >= j)
		return (ft_strdup(""));
	str = ft_strnew(j - i + 1);
	if (!str)
		return (NULL);
	trm = str;
	while (s[i] && i <= j)
		*str++ = s[i++];
	return (trm);
}
