/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:16:07 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/07 22:21:33 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		set_node(t_node *node, t_int connect_state,
		t_int weight, t_uint parent)
{
	node->weight = weight;
	node->marked = 1;
	node->parent = parent;
	if (node->separate)
	{
		if (connect_state == NEGATIVE)
			node->marked_sep = MARKED_OUT;
		else
			node->marked_sep = MARKED_IN;
	}
}

void		graph_clear_state(t_graph *graph)
{
	t_uint	i;

	i = 0;
	while (i < graph->size)
	{
		graph->nodes[i]->marked = 0;
		graph->nodes[i]->weight = 0;
		graph->nodes[i]->parent = 0;
		graph->nodes[i]->in_queue = 0;
		graph->nodes[i]->in_new_path = 0;
		i++;
	}
	graph->nodes[graph->start]->separate = 0;
	graph->nodes[graph->end]->separate = 0;
}

t_connect	*iter_all(t_iter *iter)
{
	return ((iter->i != iter->connects_count) ?
			iter->connects + (iter->i)++ : NULL);
}

t_iter		*iter_init(t_iter *iter, t_node *node, t_uint type)
{
	iter->connects_count = node->connects_count;
	iter->i = 0;
	iter->connects = (t_connect*)(node + 1);
	iter->func = type;
	return (iter);
}

t_connect	*get_connect(t_node *src, t_uint dst)
{
	t_uint			bot;
	t_uint			top;
	long long		tmp;
	t_connect		*connects;
	t_uint			connects_count;

	connects = (t_connect*)(src + 1);
	connects_count = src->connects_count;
	if (!connects_count)
		return (NULL);
	top = connects_count - 1;
	bot = 0;
	while (bot != top)
	{
		tmp = (long long)dst - (long long)(connects[bot + (top - bot) / 2].dst);
		if (!tmp)
			return (connects + bot + (top - bot) / 2);
		if (tmp < 0)
			top = bot + (top - bot) / 2;
		else
			bot += (top - bot) / 2 + 1;
	}
	tmp = (long long)dst - (long long)(connects[bot].dst);
	return (tmp ? NULL : connects + bot);
}
