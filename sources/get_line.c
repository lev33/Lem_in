/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:09:30 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/22 18:52:09 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

t_bool			is_command(char *str)
{
	if (str)
	{
		if (ft_strlen(str) > 1 && !ft_strncmp(str, "##", 2))
			return (true);
	}
	return (false);
}

t_bool			is_comment(char *str)
{
	if (str)
	{
		if (ft_strlen(str) && !is_command(str) && !ft_strncmp(str, "#", 1))
			return (true);
	}
	return (false);
}

static t_bool	is_room_name(char *str)
{
	if (str && ft_strlen(str))
	{
		if (str[0] != 'L' && str[0] != '#')
			return (true);
	}
	return (false);
}

t_bool			is_room(char *str)
{
	t_bool	result;
	char	**strsplit;

	result = false;
	if (!(strsplit = ft_strsplit(str, ' ')))
		ft_throw("ERROR: Can not parse room");
	if (ft_strsplit_len(strsplit) == 3)
	{
		if (is_room_name(strsplit[0])
				&& ft_isint(strsplit[1])
				&& ft_isint(strsplit[2]))
			result = true;
	}
	ft_strsplit_free(&strsplit);
	return (result);
}

char			*get_line(t_map **map)
{
	t_map	*current;
	char	*line;
	int		n;

	line = NULL;
	if ((n = get_next_line(0, &line)) == 1)
	{
		if (!(current = (t_map *)ft_memalloc(sizeof(t_map))))
			ft_throw("ERROR: Can not create line");
		current->line = line;
		current->next = *map;
		*map = current;
	}
	if (n == -1)
		ft_throw("ERROR: Reading error");
	return (line);
}
