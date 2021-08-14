/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_and_print_results.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:21:11 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/19 12:04:15 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		move(t_data *d, t_path *path)
{
	t_link	*cur;

	cur = path->head;
	while (cur->next)
		cur = cur->next;
	while (cur)
	{
		if (d->sorted_names[cur->start]->ant_number != -1 &&
				cur->end == d->graph.end)
		{
			add_result(d,
				new_result(d->sorted_names[cur->start]->ant_number, cur->end));
			d->sorted_names[cur->start]->ant_number = -1;
			d->ants_end++;
		}
		else if (d->sorted_names[cur->start]->ant_number != -1)
		{
			add_result(d,
				new_result(d->sorted_names[cur->start]->ant_number, cur->end));
			d->sorted_names[cur->end]->ant_number =
				d->sorted_names[cur->start]->ant_number;
			d->sorted_names[cur->start]->ant_number = -1;
		}
		cur = cur->prev;
	}
}

static void		move_on_paths(t_data *d)
{
	t_path	*current;

	current = d->paths;
	while (current)
	{
		move(d, current);
		current = current->next;
	}
}

static void		start_move(t_data *d, t_path *path)
{
	if (path->head->end == d->graph.end)
	{
		d->ants_start--;
		d->ants_end++;
		add_result(d,
				new_result(++(d->ant_number), path->head->end));
	}
	else
	{
		d->ants_start--;
		d->sorted_names[path->head->end]->ant_number = ++(d->ant_number);
		add_result(d,
				new_result(d->sorted_names[path->head->end]->ant_number,
														path->head->end));
	}
}

static void		move_from_start(t_data *d)
{
	t_path	*current;

	current = d->paths;
	while (current && d->ants_start)
	{
		if (d->ants_start > current->diff)
			start_move(d, current);
		current = current->next;
	}
}

void			move_ants_and_print_results(t_data *d)
{
	while (d->ants_start || d->ant_number != d->ants_end)
	{
		move_on_paths(d);
		move_from_start(d);
		print_results(d);
		results_free(&(d->results));
		d->results = NULL;
	}
}
