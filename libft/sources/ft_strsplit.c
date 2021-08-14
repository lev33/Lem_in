/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:49:32 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/17 11:27:46 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			arr_length(char const *s, char c)
{
	int	len;

	len = 0;
	if (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	while (*s != 0)
	{
		if (*s != c && s[-1] == c)
			len++;
		s++;
	}
	return (len + 1);
}

static char			**ft_free_strarr(char **arr)
{
	size_t i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	return (NULL);
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**arr;

	if (s == NULL)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * arr_length(s, c))))
		return (NULL);
	j = 0;
	while (*s != 0)
	{
		i = 0;
		while (s[i] != c && s[i] != 0)
			i++;
		if (i)
		{
			if (!(arr[j++] = ft_strncpy(ft_strnew(i), s, i)))
				return (ft_free_strarr(arr));
			s = &s[i];
		}
		else
			s++;
	}
	arr[j] = NULL;
	return (arr);
}
