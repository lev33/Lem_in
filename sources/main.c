/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:42:45 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/10 16:27:07 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <errno.h>

static int		find_new_path(t_graph *graph)
{
	t_queue		queue;
	t_node		*end_node;
	t_vertex	tmp;

	tmp.index = graph->start;
	tmp.weight = 0;
	queue_init(&queue, sizeof(t_vertex), 256);
	queue_add_head(&queue, &tmp);
	graph_clear_state(graph);
	set_node(graph->nodes[graph->start], 0, 0, 0);
	end_node = graph->nodes[graph->end];
	while (end_node->marked == 0 && queue.curlen)
		scan_head_queue_edges(graph, &queue);
	queue_del(&queue);
	(end_node->marked) ? reverse_new_path(graph) : 0;
	return (end_node->marked);
}

static void		find_paths(t_data *d, t_graph *graph)
{
	t_uint		max_paths;
	t_uint		current_moves;

	max_paths = graph->nodes[graph->start]->connects_count;
	if (max_paths > graph->nodes[graph->end]->connects_count)
		max_paths = graph->nodes[graph->end]->connects_count;
	d->moves = __UINT32_MAX__;
	while (find_new_path(graph))
	{
		d->paths_count++;
		reset_paths(d, graph);
		if ((current_moves = d->tmp_paths->moves) <= d->moves)
		{
			d->moves = d->tmp_paths->moves;
			if (d->paths)
				paths_free(&(d->paths));
			d->paths = d->tmp_paths;
		}
		else
			paths_free(&(d->tmp_paths));
		if (current_moves > d->moves || d->paths_count == max_paths)
			break ;
	}
	if (!d->paths_count)
		ft_throw("ERROR: No path from start to end");
}

static void		read_map_and_get_data(t_data *d, t_map **map)
{
	d->line = NULL;
	get_ants(d, map);
	d->ants_end = 0;
	d->ant_number = 0;
	d->rooms = NULL;
	d->start = NULL;
	d->end = NULL;
	d->rooms_count = 0;
	get_rooms(d, map);
	d->links = NULL;
	get_links(d, map);
	d->paths = NULL;
	d->tmp_paths = NULL;
	d->results = NULL;
	d->paths_count = 0;
}

static void		start_lemin(t_bool paths)
{
	t_map		*map;
	t_data		*data;

	map = NULL;
	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		ft_throw("ERROR: Can not create data");
	read_map_and_get_data(data, &map);
	find_paths(data, &(data->graph));
	print_and_free_map(&map);
	if (paths)
		print_paths(data);
	move_ants_and_print_results(data);
	free_data(&data);
}

int				main(int argc, char **argv)
{
	t_bool	print_paths;
	t_bool	help;

	errno = 0;
	print_paths = false;
	help = false;
	while (argc >= 2
			&& (!ft_strcmp(argv[1], "-p") || !ft_strcmp(argv[1], "-h")))
	{
		if (!ft_strcmp(argv[1], "-p"))
			print_paths = true;
		else if (!ft_strcmp(argv[1], "-h"))
			help = true;
		argv++;
		argc--;
	}
	if (argc == 1 && !help)
		start_lemin(print_paths);
	else if (help)
		ft_putendl("-p\tprint paths\n-h\thelp");
	else
		ft_putendl("Usage: ./lem-in < MAP_FILE");
	return (0);
}
