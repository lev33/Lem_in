/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:26:28 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/18 11:19:52 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reverse(t_map **map)
{
	t_map	*prev;
	t_map	*current;
	t_map	*next;

	prev = NULL;
	current = *map;
	next = NULL;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*map = prev;
}

void		print_and_free_map(t_map **map)
{
	t_map		*current;
	t_map		*delete;

	reverse(map);
	current = *map;
	while (current)
	{
		ft_putendl(current->line);
		delete = current;
		current = current->next;
		free(delete->line);
		free(delete);
	}
	ft_putendl(NULL);
	*map = NULL;
}

void		print_paths(t_data *d)
{
	t_path	*current_path;
	t_link	*current_link;

	current_path = d->paths;
	ft_putstr("#Here is the number of printed paths: ");
	ft_putnbr(d->paths_count);
	ft_putstr("\n#Here is the number of lines in result: ");
	ft_putnbr(d->moves);
	ft_putstr("\n\n");
	while (current_path && (current_link = current_path->head))
	{
		ft_putstr("Path length: ");
		ft_putnbr(current_path->length);
		ft_putstr("\nPath: ");
		ft_putstr(d->sorted_names[current_link->start]->name);
		while (current_link)
		{
			ft_putstr(" - ");
			ft_putstr(d->sorted_names[current_link->end]->name);
			current_link = current_link->next;
		}
		ft_putendl(NULL);
		current_path = current_path->next;
	}
	ft_putendl(NULL);
}

void		print_results(t_data *d)
{
	t_result	*current;

	current = d->results;
	while (current)
	{
		if (current != d->results)
			ft_putchar(' ');
		ft_putchar('L');
		ft_putnbr(current->ant_number);
		ft_putchar('-');
		ft_putstr(d->sorted_names[current->node]->name);
		current = current->next;
	}
	ft_putendl(NULL);
}
