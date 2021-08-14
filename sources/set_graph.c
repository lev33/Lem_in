/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 15:19:27 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 15:36:39 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			graph_add_connect(t_graph *graph, t_uint src, t_uint dst)
{
	t_node		*node;
	t_connect	*con;

	node = graph->nodes[src];
	con = ((t_connect *)(node + 1)) + (node->connects_count)++;
	con->dst = dst;
	con->state = GENERAL;
}

static void			swap(t_connect *v, int i, int j)
{
	t_connect temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

static void			ft_qsort(t_connect *v, int left, int right)
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
		if (v[i].dst < v[left].dst)
			swap(v, ++last, i);
		i++;
	}
	swap(v, left, last);
	ft_qsort(v, left, last - 1);
	ft_qsort(v, last + 1, right);
}

void				sort_connects(t_data *d, t_graph *graph)
{
	size_t i;

	i = 0;
	while (i < graph->size)
	{
		ft_qsort(((t_connect*)(graph->nodes[i] + 1)), 0,
								graph->nodes[i]->connects_count - 1);
		i++;
	}
	i = 0;
	while (i < graph->size)
	{
		if (d->sorted_names[i]->name == d->start->name)
			graph->start = i;
		if (d->sorted_names[i]->name == d->end->name)
			graph->end = i;
		i++;
	}
}

void				set_graph(t_data *d, t_graph *graph)
{
	size_t	i;
	t_link	*current;
	void	*current_pos;

	i = 0;
	current = d->links;
	graph->size = d->rooms_count;
	graph->nodes = (t_node**)ft_memalloc(sizeof(t_node*) * graph->size);
	graph->mem = ft_memalloc(sizeof(t_node) * graph->size +
			sizeof(t_connect) * d->links_count * 2);
	current_pos = graph->mem;
	while (i < graph->size)
	{
		graph->nodes[i] = current_pos;
		current_pos +=
		sizeof(t_node) + sizeof(t_connect) * (d->sorted_names[i])->room_links;
		i++;
	}
	while (current)
	{
		graph_add_connect(graph, current->start, current->end);
		graph_add_connect(graph, current->end, current->start);
		current = current->next;
	}
	sort_connects(d, graph);
}
