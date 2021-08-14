/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:41:04 by ligeorgi          #+#    #+#             */
/*   Updated: 2019/09/30 15:25:05 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 32

typedef struct			s_flist
{
	char				*s;
	int					fd;
	struct s_flist		*next;
}						t_flist;

int						get_next_line(const int fd, char **line);

#endif
