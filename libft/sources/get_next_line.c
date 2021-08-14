/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:41:19 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/10/01 11:03:34 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

static t_flist		*get_list(t_flist **head, int fd)
{
	t_flist			*list;

	list = *head;
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	list = (t_flist*)malloc(sizeof(t_flist));
	if (!list)
		return (NULL);
	list->s = ft_strnew(1);
	if (!list->s)
	{
		free(list);
		return (NULL);
	}
	list->fd = fd;
	list->next = *head;
	*head = list;
	return (*head);
}

static int			get_line(char **s, char **line)
{
	char			*end;
	char			*str;

	str = *s;
	end = ft_strchr(str, '\n');
	if (end)
		*line = ft_strsub(str, 0, end - str);
	else
		*line = ft_strdup(str);
	if (!*line)
		return (-1);
	if (end)
		*s = ft_strsub(str, (unsigned int)(ft_strlen(*line) + 1),
				(size_t)(ft_strlen(str) - (ft_strlen(*line) + 1)));
	else
		*s = ft_strnew(1);
	if (!*s)
		return (-1);
	ft_strdel(&str);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static t_flist	*head_of_list;
	t_flist			*list;
	char			buf[BUFF_SIZE + 1];
	char			*str;
	ssize_t			n;

	if (fd < 0 || !(list = get_list(&head_of_list, fd)) || !line)
		return (-1);
	if (ft_strchr(list->s, '\n'))
		return (get_line(&list->s, line));
	while (!ft_strchr(list->s, '\n') && (n = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[n] = '\0';
		str = list->s;
		list->s = ft_strjoin(list->s, buf);
		if (!list->s)
			return (-1);
		ft_strdel(&str);
	}
	if (n == -1)
		return (-1);
	if (!ft_strlen(list->s))
		return (0);
	else
		return (get_line(&list->s, line));
}
