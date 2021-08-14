/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:35:59 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/07 22:18:17 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <errno.h>

void			ft_throw(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

void			ft_strsplit_free(char ***strsplit)
{
	char	**current;

	if (strsplit && *strsplit)
	{
		current = ((*strsplit));
		while ((*current))
			free((*(current++)));
		free((*strsplit));
		(*strsplit) = NULL;
	}
}

size_t			ft_strsplit_len(char **strsplit)
{
	size_t	size;

	size = 0;
	if (strsplit)
		while (*strsplit)
		{
			size++;
			strsplit++;
		}
	return (size);
}

t_uint			binarysearch(t_data *d, char *str)
{
	int low;
	int high;
	int middle;

	low = 0;
	high = d->rooms_count - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (ft_strcmp(str, d->sorted_names[middle]->name) < 0)
			high = middle - 1;
		else if (ft_strcmp(str, d->sorted_names[middle]->name) > 0)
			low = middle + 1;
		else
			return (middle);
	}
	return (-1);
}
