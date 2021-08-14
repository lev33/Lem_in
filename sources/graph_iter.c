/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:09:34 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/19 12:09:34 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static t_connect		*iter_not_forbidden(t_iter *iter)
{
	t_connect	*tmp;

	while ((tmp = iter_all(iter)) && (tmp->state == FORBIDDEN))
		;
	return (tmp);
}

static t_connect		*iter_negative(t_iter *iter)
{
	t_connect	*tmp;

	while ((tmp = iter_all(iter)) && !(tmp->state == NEGATIVE))
		;
	return (tmp);
}

static t_connect		*iter_forbidden(t_iter *iter)
{
	t_connect	*tmp;

	while ((tmp = iter_all(iter)) && !(tmp->state == FORBIDDEN))
		;
	return (tmp);
}

static t_connect		*iter_general(t_iter *iter)
{
	t_connect	*tmp;

	while ((tmp = iter_all(iter)) && (tmp->state != GENERAL))
		;
	return (tmp);
}

static t_connect		*(*g_iter_func[])(t_iter *iter) = {
	iter_all,
	iter_not_forbidden,
	iter_negative,
	iter_forbidden,
	iter_general
};

t_connect				*iter_next(t_iter *iter)
{
	return (g_iter_func[iter->func](iter));
}
