/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_head_queue_edges.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:48:53 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/19 11:49:12 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void			add_vertex_in_queue(t_graph *graph, t_queue *queue,
		t_vertex vertex)
{
	size_t cur;
	size_t next;

	cur = queue->head;
	if (queue->curlen == 0 ||
			((get_vertex(queue, cur))->weight >= vertex.weight))
		queue_add_head(queue, &vertex);
	else if ((get_vertex(queue, queue->tail))->weight <=
			vertex.weight)
		queue_add_tail(queue, &vertex);
	else
	{
		next = queue->list[queue->head].next;
		while ((get_vertex(queue, next))->weight < vertex.weight)
		{
			cur = next;
			next = queue->list[next].next;
		}
		queue_add_after(queue, cur, &vertex);
	}
	graph->nodes[vertex.index]->in_queue = 1;
}

static void			change_dst_weight(t_graph *graph, t_queue *queue,
		t_uint item, t_int weight)
{
	t_vertex	*tmp;
	size_t		cur;
	size_t		next;

	cur = queue->head;
	next = queue->list[cur].next;
	if ((tmp = (get_vertex(queue, cur)))->index == item)
	{
		tmp->weight = weight;
		return ;
	}
	while ((tmp = (get_vertex(queue, next)))->index != item)
	{
		cur = next;
		next = queue->list[cur].next;
	}
	tmp = ((t_vertex *)queue_pop_after(queue, cur));
	tmp->weight = weight;
	add_vertex_in_queue(graph, queue, *tmp);
}

static void			check_edge_dst_node(t_graph *graph, t_queue *queue,
		t_vertex src, t_edge edge)
{
	t_vertex		new;

	new.index = edge.s_d->dst;
	new.weight = src.weight + edge.s_d->state;
	if (edge.dst->marked == 0)
	{
		add_vertex_in_queue(graph, queue, new);
		set_node(edge.dst, edge.s_d->state, new.weight, src.index);
	}
	else if (edge.dst->separate && edge.dst->marked_sep == MARKED_IN &&
			edge.s_d->state == NEGATIVE)
	{
		edge.dst->weight <= new.weight ? (edge.dst->marked_sep = MARKED_OUT) :
			set_node(edge.dst, edge.s_d->state, new.weight, src.index);
		(edge.dst->in_queue == 0) ? add_vertex_in_queue(graph, queue, new) :
			change_dst_weight(graph, queue, edge.s_d->dst, new.weight);
	}
	else if (edge.dst->weight > new.weight)
	{
		set_node(edge.dst, edge.s_d->state, new.weight, src.index);
		(edge.dst->in_queue == 0) ? add_vertex_in_queue(graph, queue, new) :
			change_dst_weight(graph, queue, edge.s_d->dst, new.weight);
	}
}

void				scan_head_queue_edges(t_graph *graph, t_queue *queue)
{
	t_iter			iter[1];
	t_vertex		src;
	t_edge			edge;

	src = *(t_vertex *)queue_pop_head(queue);
	edge.src = graph->nodes[src.index];
	edge.src->in_queue = 0;
	if (edge.src->separate && edge.src->marked_sep == MARKED_IN)
		iter_init(iter, edge.src, ITER_NEGATIVE);
	else
		iter_init(iter, edge.src, ITER_NOT_FORBIDDEN);
	while ((edge.s_d = iter_next(iter)))
	{
		edge.dst = graph->nodes[edge.s_d->dst];
		check_edge_dst_node(graph, queue, src, edge);
	}
}
