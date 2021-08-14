/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:55:40 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 13:05:54 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void		add_path(t_data *d, t_path *path)
{
	t_path	*previous;
	t_path	*current;

	previous = NULL;
	current = d->tmp_paths;
	if (current)
	{
		while (current && path->length > current->length)
		{
			previous = current;
			current = current->next;
		}
		if (!previous)
			d->tmp_paths = path;
		else
			previous->next = path;
		path->next = current;
	}
	else
		d->tmp_paths = path;
}

static t_path	*create_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)ft_memalloc(sizeof(t_path))))
		ft_throw("ERROR: Can not create path");
	path->head = NULL;
	path->length = 0;
	path->diff = 0;
	path->next = NULL;
	return (path);
}

static void		path_add_link(t_path *path, t_link *link)
{
	t_link	*previous;
	t_link	*current;

	link->next = NULL;
	link->prev = NULL;
	previous = NULL;
	current = path->head;
	if (current)
	{
		while (current)
		{
			previous = current;
			current = current->next;
		}
		link->prev = previous;
		previous->next = link;
	}
	else
		path->head = link;
	path->length++;
}

static void		continue_path(t_data *d, t_path *path, t_uint node)
{
	t_connect	*tmp;
	t_uint		prev;
	t_link		*link;
	t_iter		iter[1];

	link = path->head;
	prev = node;
	iter_init(iter, d->graph.nodes[node], ITER_FORBIDDEN);
	while (link->end != d->graph.end)
	{
		tmp = iter_next(iter);
		link = new_link(d, prev, tmp->dst, 0);
		path_add_link(path, link);
		prev = tmp->dst;
		iter_init(iter, d->graph.nodes[tmp->dst], ITER_FORBIDDEN);
	}
}

void			reset_paths(t_data *d, t_graph *graph)
{
	t_iter		iter[1];
	t_connect	*tmp;
	t_link		*link;
	t_path		*paths;

	d->tmp_paths = NULL;
	iter_init(iter, graph->nodes[graph->start], ITER_FORBIDDEN);
	while ((tmp = iter_next(iter)))
	{
		paths = create_path();
		link = new_link(d, graph->start, tmp->dst, 0);
		path_add_link(paths, link);
		continue_path(d, paths, tmp->dst);
		add_path(d, paths);
	}
	paths = d->tmp_paths;
	d->paths_count = 0;
	while (paths)
	{
		d->paths_count++;
		paths = paths->next;
	}
	count_path_diffs(d);
	count_moves(d, d->ants_start, d->paths_count);
}
