/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:24:15 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/19 12:00:11 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				count_moves(t_data *d, t_uint ants, t_uint n)
{
	t_uint		tmp;
	t_uint		diffs[d->paths_count];
	t_path		*path;
	t_uint		i;

	path = d->tmp_paths;
	i = 0;
	while (path)
	{
		diffs[i++] = path->diff;
		path = path->next;
	}
	i = 0;
	while (n > 0)
		if ((__int64_t)ants - (n - 1) > diffs[n - 1])
		{
			tmp = (ants - (n - 1) - diffs[n - 1]) / n;
			tmp += (tmp) ? 0 : 1;
			i += tmp;
			ants -= (n * tmp);
		}
		else
			n--;
	d->tmp_paths->moves = i + d->tmp_paths->length - 1;
}

void				count_path_diffs(t_data *d)
{
	int		diff;
	t_path	*path;
	t_path	*current;

	path = d->tmp_paths;
	while (path)
	{
		diff = 0;
		current = d->tmp_paths;
		while (current != path)
		{
			diff += path->length - current->length;
			current = current->next;
		}
		path->diff = diff;
		path = path->next;
	}
}

t_result			*new_result(int ant_number, t_uint node)
{
	t_result	*result;

	if (!(result = (t_result *)ft_memalloc(sizeof(t_result))))
		ft_throw("ERROR: Can not create result");
	result->ant_number = ant_number;
	result->node = node;
	result->next = NULL;
	return (result);
}

void				add_result(t_data *d, t_result *result)
{
	t_result	*previous;
	t_result	*current;

	previous = NULL;
	current = d->results;
	if (current)
	{
		while (current && result->ant_number > current->ant_number)
		{
			previous = current;
			current = current->next;
		}
		if (!previous)
			d->results = result;
		else
			previous->next = result;
		result->next = current;
	}
	else
		d->results = result;
}
