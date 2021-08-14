/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_queue_change.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:05:25 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/12/18 11:21:10 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void			queue_add_head(t_queue *self, void *data)
{
	size_t	item_place;

	item_place = queue_get_space(self);
	ft_memmove(self->items + self->item_size * item_place, data,
			self->item_size);
	self->list[item_place].self = item_place;
	if (self->curlen++ == 0)
		self->tail = item_place;
	self->list[item_place].next = self->head;
	self->head = item_place;
}

void			queue_add_tail(t_queue *self, void *data)
{
	size_t	item_place;

	item_place = queue_get_space(self);
	ft_memmove(self->items + self->item_size * item_place, data,
			self->item_size);
	self->list[item_place].self = item_place;
	self->list[item_place].next = QUEUE_EMPTY;
	if (self->curlen++ == 0)
		self->head = item_place;
	else
		self->list[self->tail].next = item_place;
	self->tail = item_place;
}

void			queue_add_after(t_queue *self, size_t item,
		void *data)
{
	size_t			item_place;
	t_list_item		*tmp;

	if (self->curlen == 0)
		return (queue_add_head(self, data));
	item_place = queue_get_space(self);
	ft_memmove(self->items + self->item_size * item_place, data,
			self->item_size);
	tmp = self->list + item;
	self->list[item_place].self = item_place;
	self->list[item_place].next = tmp->next;
	tmp->next = item_place;
	self->curlen++;
}

void			*queue_pop_head(t_queue *self)
{
	size_t	item_place;

	if (self->curlen == 0)
		return (NULL);
	item_place = self->head;
	self->head = self->list[self->head].next;
	self->free_space_mask[item_place / 64] |= (1llu << item_place % 64);
	(self->curlen)--;
	return (self->items + item_place * self->item_size);
}

void			*queue_pop_after(t_queue *self, size_t item)
{
	size_t	next;

	if (self->curlen == 0)
		return (NULL);
	if (self->curlen == 1)
		return (queue_pop_head(self));
	next = self->list[item].next;
	self->list[item].next = self->list[next].next;
	if (self->tail == next)
		self->tail = item;
	self->free_space_mask[next / 64] |= (1llu << next % 64);
	(self->curlen)--;
	return (self->items + next * self->item_size);
}
