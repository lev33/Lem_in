/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_new_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:19:02 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/07 22:20:26 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void		find_new_parent(t_node *node, t_graph *graph)
{
	t_int				min_weight;
	t_connect			*connect;
	t_int				new_wt;
	t_iter				iter[1];
	t_uint				res;

	min_weight = __INT32_MAX__;
	res = node->parent;
	iter_init(iter, node, ITER_GENERAL);
	while ((connect = iter_next(iter)))
		if ((new_wt = graph->nodes[connect->dst]->weight) < min_weight)
		{
			min_weight = new_wt;
			res = connect->dst;
		}
	node->parent = res;
}

static void		reverse_edge_states(t_edge edge)
{
	if (edge.s_d->state == GENERAL)
	{
		edge.s_d->state = NEGATIVE;
		edge.d_s->state = FORBIDDEN;
		edge.src->separate = 1;
		edge.dst->separate = 1;
	}
	else
	{
		edge.s_d->state = GENERAL;
		edge.d_s->state = GENERAL;
		edge.dst->separate = 0;
	}
}

void			reverse_new_path(t_graph *graph)
{
	t_uint				current;
	t_edge				edge;
	t_iter				iter[1];

	current = graph->end;
	edge.src = graph->nodes[current];
	while (current != graph->start)
	{
		edge.dst = graph->nodes[edge.src->parent];
		edge.s_d = get_connect(edge.src, edge.src->parent);
		edge.d_s = get_connect(edge.dst, current);
		if (edge.dst->separate && edge.dst->marked_sep == MARKED_OUT &&
				edge.s_d->state == GENERAL)
			(edge.dst->parent =
				iter_next(iter_init(iter, edge.dst, ITER_FORBIDDEN))->dst);
		if (edge.dst->in_new_path)
			find_new_parent(edge.dst, graph);
		edge.dst->in_new_path = 1;
		reverse_edge_states(edge);
		current = edge.src->parent;
		edge.src = edge.dst;
	}
	edge.src->separate = 0;
}
