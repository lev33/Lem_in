/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 14:07:15 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/12 14:08:55 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_ants(t_data *d, t_map **map)
{
	if ((d->line = get_line(map)))
	{
		if (ft_isint(d->line))
		{
			d->ants_start = ft_atoi(d->line);
			d->line = NULL;
			if (d->ants_start <= 0)
				ft_throw("ERROR: Number of ants is wrong");
		}
		else
			ft_throw("ERROR: Number of ants is wrong");
	}
}
