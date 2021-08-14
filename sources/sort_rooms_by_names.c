/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_rooms_by_names.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:30:20 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 14:34:51 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		swap(t_room **v, int i, int j)
{
	t_room *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

static void		ft_qsort(t_room **v, int left, int right)
{
	int i;
	int last;

	if (left >= right)
		return ;
	swap(v, left, (left + right) / 2);
	last = left;
	i = left + 1;
	while (i <= right)
	{
		if (ft_strcmp(v[i]->name, v[left]->name) < 0)
			swap(v, ++last, i);
		i++;
	}
	swap(v, left, last);
	ft_qsort(v, left, last - 1);
	ft_qsort(v, last + 1, right);
}

void			sort_rooms_by_names(t_data *d)
{
	int		i;
	t_room	*current;

	i = 0;
	current = d->rooms;
	if (!(d->sorted_names =
					(t_room**)ft_memalloc(d->rooms_count * sizeof(t_room*))))
		ft_throw("ERROR: Can not create sorted names");
	while (current)
	{
		d->sorted_names[i++] = current;
		current = current->next;
	}
	ft_qsort(d->sorted_names, 0, d->rooms_count - 1);
}
