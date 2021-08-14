/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 14:36:13 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/17 11:54:09 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free_list(t_list *lst)
{
	t_list	*temp;
	t_list	*tmp;

	temp = lst->next;
	while (temp)
	{
		temp = temp->next;
		tmp = temp;
		free(tmp);
	}
	free(lst);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *temp;
	t_list *new;
	t_list *start;

	if (!lst || !f)
		return (NULL);
	temp = f(lst);
	new = ft_lstnew(temp->content, temp->content_size);
	if (!new)
		return (NULL);
	lst = lst->next;
	start = new;
	while (lst)
	{
		temp = f(lst);
		new->next = ft_lstnew(temp->content, temp->content_size);
		if (!new->next)
		{
			ft_free_list(start);
			return (NULL);
		}
		lst = lst->next;
		new = new->next;
	}
	return (start);
}
