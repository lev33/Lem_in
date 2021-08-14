/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 19:47:56 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 19:49:18 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	results_free(t_result **current)
{
	t_result	*delete;

	if (current)
		while ((*current))
		{
			delete = (*current);
			(*current) = (*current)->next;
			free(delete);
			delete = NULL;
		}
}

void	paths_free(t_path **current)
{
	t_path	*delete;

	if (current)
		while ((*current))
		{
			delete = (*current);
			(*current) = (*current)->next;
			links_free(&(delete->head));
			free(delete);
			delete = NULL;
		}
}

void	links_free(t_link **current)
{
	t_link	*delete;

	if (current)
		while ((*current))
		{
			delete = (*current);
			(*current) = (*current)->next;
			free(delete);
			delete = NULL;
		}
}

void	rooms_free(t_room **current)
{
	t_room	*delete;

	if (current)
		while ((*current))
		{
			delete = (*current);
			(*current) = (*current)->next;
			free(delete->name);
			free(delete);
			delete = NULL;
		}
}

void	free_data(t_data **d)
{
	if (d && *d)
	{
		results_free(&((*d)->results));
		paths_free(&((*d)->paths));
		links_free(&((*d)->links));
		rooms_free(&((*d)->rooms));
		free((*d)->sorted_names);
		free((*d)->graph.nodes);
		free((*d)->graph.mem);
		free((*d));
		(*d) = NULL;
	}
}
