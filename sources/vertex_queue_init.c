/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_queue_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:04:22 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/11/19 11:47:24 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_vertex		*get_vertex(t_queue *self, size_t item)
{
	return ((t_vertex *)(self->items + item * self->item_size));
}

void			queue_init(t_queue *self, size_t item_size,
		size_t init_len)
{
	size_t	free_mem_mask_size;

	self->item_size = item_size;
	self->curlen = 0;
	self->max_size = init_len;
	self->head = QUEUE_EMPTY;
	self->tail = QUEUE_EMPTY;
	free_mem_mask_size = (init_len / 64 + ((init_len % 64) ? 1 : 0)) *
		sizeof(__uint64_t);
	self->mem = ft_memalloc((item_size + sizeof(t_list_item)) * init_len +
			free_mem_mask_size);
	self->free_space_mask = self->mem;
	self->items = self->mem + free_mem_mask_size;
	self->list = self->mem + free_mem_mask_size + init_len * item_size;
	ft_memset(self->free_space_mask, -1, free_mem_mask_size);
}

void			queue_del(t_queue *self)
{
	if (self->mem)
		free(self->mem);
	ft_bzero(self, sizeof(t_queue));
}

void			queue_extend(t_queue *self)
{
	void	*tmp;
	size_t	old_size;
	size_t	new_free_mem_mask_size;
	size_t	old_free_mem_mask_size;

	old_size = self->max_size;
	self->max_size *= 2;
	new_free_mem_mask_size = (self->max_size / 64 + ((self->max_size % 64)
				? 1 : 0)) * sizeof(__uint64_t);
	old_free_mem_mask_size = (old_size / 64 + ((old_size % 64) ? 1 : 0)) *
		sizeof(__uint64_t);
	tmp = ft_memalloc((self->item_size + sizeof(t_list_item)) * self->max_size +
			new_free_mem_mask_size);
	ft_memset(tmp, -1, new_free_mem_mask_size);
	self->free_space_mask = ft_memcpy(tmp, self->mem, old_free_mem_mask_size);
	self->items = ft_memcpy(tmp + new_free_mem_mask_size, self->items,
			old_size * self->item_size);
	self->list = ft_memcpy(tmp + new_free_mem_mask_size + self->max_size *
			self->item_size, self->list, old_size * sizeof(t_list_item));
	free(self->mem);
	self->mem = tmp;
}

size_t			queue_get_space(t_queue *self)
{
	size_t		res;
	__uint64_t	tmp;
	__uint64_t	z;
	int			i;

	i = 0;
	z = 1llu;
	res = (size_t)-1;
	if (self->curlen == self->max_size)
		queue_extend(self);
	while (self->free_space_mask[++res] == 0)
		;
	tmp = self->free_space_mask[res];
	while ((z & tmp) == 0)
	{
		z = z << 1;
		i++;
	}
	self->free_space_mask[res] &= ~(1llu << i);
	return (res * 64 + i);
}
