/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:12:09 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 14:15:34 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_rooms(t_link *link, t_link *current)
{
	if ((link->start == current->start && link->end == current->end) ||
			(link->start == current->end && link->end == current->start))
		ft_throw("ERROR: Link doubles");
}

static void		add_link(t_data *d, t_link *link)
{
	t_link	*current;

	current = d->links;
	if (current)
	{
		while (current->next)
		{
			check_rooms(link, current);
			current = current->next;
		}
		check_rooms(link, current);
		link->prev = current;
		current->next = link;
	}
	else
		d->links = link;
}

t_link			*new_link(t_data *d, int start, int end, int count_links)
{
	t_link	*link;

	if (!(link = (t_link *)ft_memalloc(sizeof(t_link))))
		ft_throw("ERROR: Can not create link");
	link->start = start;
	link->end = end;
	if (count_links)
	{
		d->sorted_names[start]->room_links++;
		d->sorted_names[end]->room_links++;
	}
	return (link);
}

static t_link	*create_link(t_data *d, char *str)
{
	char	*tmp;
	char	*start_name;
	char	*end_name;
	int		start;
	int		end;

	tmp = str;
	while ((tmp = ft_strchr(tmp + 1, '-')))
	{
		if (!(start_name = ft_strsub(str, 0, tmp - str)))
			ft_throw("ERROR: Can not create link");
		if (!(end_name = ft_strsub(tmp + 1, 0, ft_strlen(tmp + 1))))
			ft_throw("ERROR: Can not create link");
		start = binarysearch(d, start_name);
		end = binarysearch(d, end_name);
		free(start_name);
		free(end_name);
		if (start != -1 && end != -1 && start != end)
		{
			d->links_count++;
			return (new_link(d, start, end, 1));
		}
	}
	return (NULL);
}

void			get_links(t_data *d, t_map **map)
{
	t_link	*link;

	while (d->line || (d->line = get_line(map)))
	{
		if (!is_comment(d->line) && !is_command(d->line))
		{
			if (!(link = create_link(d, d->line)))
				ft_throw("ERROR: Can not parse link");
			add_link(d, link);
		}
		d->line = NULL;
	}
	if (!d->links)
		ft_throw("ERROR: No links");
	set_graph(d, &(d->graph));
	links_free(&(d->links));
}
