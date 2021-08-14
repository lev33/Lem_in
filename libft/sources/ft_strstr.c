/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 12:50:03 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/12 12:59:01 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *str, const char *to_find)
{
	unsigned int pos;
	unsigned int i;

	if (!*to_find)
		return ((char*)str);
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == to_find[0])
		{
			i = 1;
			while (to_find[i] && str[pos + i] == to_find[i])
				i++;
			if (to_find[i] == '\0')
				return ((char*)&str[pos]);
		}
		pos++;
	}
	return (0);
}
