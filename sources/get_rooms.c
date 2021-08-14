/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:15:53 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/18 11:32:55 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		check_room(t_room *room, t_room *current)
{
	if (!ft_strcmp(room->name, current->name))
		ft_throw("ERROR: Room name doubles");
	if (room->x == current->x && room->y == current->y)
		ft_throw("ERROR: Room coordinates doubles");
}

static t_room	*create_room(char *str, t_type type)
{
	char		**strsplit;
	t_room		*room;

	if (!(strsplit = ft_strsplit(str, ' ')))
		ft_throw("ERROR: Can not create room");
	if (!(room = (t_room *)ft_memalloc(sizeof(t_room))))
		ft_throw("ERROR: Can not create room");
	if (!(room->name = ft_strdup(strsplit[0])))
		ft_throw("ERROR: Can not create room");
	room->x = ft_atoi(strsplit[1]);
	room->y = ft_atoi(strsplit[2]);
	room->type = type;
	room->room_links = 0;
	room->ant_number = -1;
	room->next = NULL;
	ft_strsplit_free(&strsplit);
	return (room);
}

static void		add_room(t_data *d, t_room *room)
{
	t_room *current;

	if (d->rooms_count == (__UINT32_MAX__ >> 2))
		ft_throw("ERROR: Too many rooms");
	if ((current = d->rooms))
	{
		while (current->next)
		{
			check_room(room, current);
			current = current->next;
		}
		check_room(room, current);
		current->next = room;
	}
	else
		d->rooms = room;
	if (room->type == START)
		d->start = room;
	else if (room->type == END)
		d->end = room;
}

void			get_rooms(t_data *d, t_map **map)
{
	t_type	type;

	type = ROOM;
	while ((d->line = get_line(map)) && (is_command(d->line)
				|| is_comment(d->line) || is_room(d->line)))
	{
		if (is_command(d->line) && !ft_strcmp(d->line, "##start"))
			type = START;
		else if (is_command(d->line) && !ft_strcmp(d->line, "##end"))
			type = END;
		else if (is_room(d->line))
		{
			add_room(d, create_room(d->line, type));
			d->rooms_count++;
			type = ROOM;
		}
		if ((type == START && d->start) || (type == END && d->end))
			ft_throw("ERROR: Two start or end rooms");
		d->line = NULL;
	}
	if (!d->start || !d->end)
		ft_throw("ERROR: No start or end room");
	sort_rooms_by_names(d);
}
