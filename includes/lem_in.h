/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:48:14 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/18 11:22:36 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft.h"
# include <stdio.h>

# define GENERAL	1
# define NEGATIVE	-1
# define FORBIDDEN	0

# define MARKED_IN	0
# define MARKED_OUT	1

# define ITER_ALL				0
# define ITER_NOT_FORBIDDEN		1
# define ITER_NEGATIVE			2
# define ITER_FORBIDDEN			3
# define ITER_GENERAL		4

# define QUEUE_EMPTY	((size_t)(-1))

typedef __uint32_t	t_uint;
typedef __int32_t	t_int;

typedef enum
{
	false,
	true
}	t_bool;

typedef enum
{
	START,
	ROOM,
	END
}	t_type;

typedef struct			s_map
{
	char				*line;
	struct s_map		*next;
}						t_map;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	t_type				type;
	t_uint				room_links;
	int					ant_number;
	struct s_room		*next;
}						t_room;

typedef struct			s_link
{
	t_uint				start;
	t_uint				end;
	struct s_link		*next;
	struct s_link		*prev;
}						t_link;

typedef struct			s_path
{
	t_link				*head;
	int					length;
	int					diff;
	t_uint				moves;
	struct s_path		*next;
}						t_path;

typedef struct			s_result
{
	int					ant_number;
	t_uint				node;
	struct s_result		*next;
}						t_result;

typedef struct			s_node
{
	t_uint		connects_count	: 30;
	t_uint		marked		: 1;
	t_uint		in_queue	: 1;
	t_uint		separate	: 1;
	t_uint		marked_sep	: 1;
	t_uint		parent		: 30;
	t_int		weight		: 31;
	t_uint		in_new_path	: 1;
}						t_node;

typedef struct			s_connect
{
	t_uint			dst	: 30;
	t_int			state	: 2;
}						t_connect;

typedef struct			s_edge
{
	t_node				*src;
	t_node				*dst;
	t_connect			*s_d;
	t_connect			*d_s;
}						t_edge;

typedef struct			s_edge_iterator
{
	t_connect			*connects;
	t_uint				i;
	t_uint				connects_count;
	t_uint				func;
}						t_iter;

typedef struct			s_graph
{
	t_node				**nodes;
	void				*mem;
	size_t				size;
	t_uint				start;
	t_uint				end;
}						t_graph;

typedef struct			s_vertex
{
	t_uint				index;
	t_int				weight;
}						t_vertex;

typedef struct			s_list_item
{
	size_t				self;
	size_t				next;
}						t_list_item;

typedef struct			s_queue
{
	void					*mem;
	__uint64_t				*free_space_mask;
	void					*items;
	t_list_item				*list;
	size_t					head;
	size_t					tail;
	size_t					curlen;
	size_t					item_size;
	size_t					max_size;
}						t_queue;

typedef struct			s_data
{
	char				*line;
	int					ants_start;
	int					ants_end;
	int					ant_number;
	int					rooms_count;
	int					links_count;
	t_uint				paths_count;
	t_uint				moves;
	t_room				**sorted_names;
	t_room				*rooms;
	t_room				*start;
	t_room				*end;
	t_link				*links;
	t_graph				graph;
	t_path				*paths;
	t_path				*tmp_paths;
	t_result			*results;
}						t_data;

char					*get_line(t_map **map);
void					get_ants(t_data *d, t_map **map);
void					get_rooms(t_data *d, t_map **map);
void					get_links(t_data *d, t_map **map);
t_link					*new_link(t_data *d, int start, int end,
														int count_links);

void					sort_rooms_by_names(t_data *d);
void					set_graph(t_data *d, t_graph *graph);

t_bool					is_command(char *str);
t_bool					is_comment(char *str);
t_bool					is_room(char *str);

t_uint					binarysearch(t_data *d, char *str);

t_result				*new_result(int ant_number, t_uint node);
void					add_result(t_data *d, t_result *result);
void					move_ants_and_print_results(t_data *d);

void					free_data(t_data **d);
void					results_free(t_result **current);
void					paths_free(t_path **current);
void					links_free(t_link **current);
void					rooms_free(t_room **current);

void					ft_throw(char *s);

void					print_and_free_map(t_map **map);
void					print_paths(t_data *d);
void					print_results(t_data *d);

void					ft_strsplit_free(char ***strsplit);
size_t					ft_strsplit_len(char **strsplit);

void					queue_init(t_queue *self, size_t item_size,
															size_t init_len);
void					queue_del(t_queue *self);
void					queue_extend(t_queue *self);
size_t					queue_get_space(t_queue *self);
t_vertex				*get_vertex(t_queue *self, size_t item);
void					queue_add_head(t_queue *self, void *data);
void					queue_add_tail(t_queue *self, void *data);
void					queue_add_after(t_queue *self, size_t item,
																void *data);
void					*queue_pop_head(t_queue *self);
void					*queue_pop_after(t_queue *self, size_t item);

void					count_moves(t_data *d, t_uint ants, t_uint n);
void					count_path_diffs(t_data *d);

void					graph_clear_state(t_graph *graph);

t_node					*graph_node(t_graph *graph, t_uint index);
t_connect				*get_connect(t_node *src, t_uint dst);

t_iter					*iter_init(t_iter *iter, t_node *node, t_uint type);
t_connect				*iter_next(t_iter *iter);
t_connect				*iter_all(t_iter *iter);

void					set_node(t_node *node, t_int connect_state,
											t_int weight, t_uint parent);

void					scan_head_queue_edges(t_graph *graph, t_queue *queue);
void					reverse_new_path(t_graph *graph);
void					reset_paths(t_data *d, t_graph *graph);

#endif
