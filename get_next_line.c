/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:41:53 by fmanetti          #+#    #+#             */
/*   Updated: 2020/01/22 16:29:40 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void		ft_cut(char **line, char **str)
{
	int		x;

	x = 0;
	if (ft_strchr(*str, '\n'))
	{
		while ((*str)[x] != '\n')
			x++;
		*line = ft_substr(*str, 0, x);
		*str = *str + x + 1; 
	}
	else
	{
		x = ft_strlen(*str);
		*line = ft_substr(*str, 0, x);
		*str = *str + x;
	}
	
}

static t_file		*create_check(int fd, t_file **head)
{
	t_file	*tmp;

	tmp = *head;
	while (tmp) 
	{
		if (fd == tmp->fd) //verifico fd
			return (tmp);
		tmp = tmp->next; //scorro la lista
	}
	//uso tmp poiché è alla fine quindi tmp = NULL
	if (!(tmp = malloc(sizeof(t_file))))
		return (NULL);
	if (!(tmp->content = malloc(1)))
		return (NULL);
	tmp->fd = fd;
	tmp->content[0] = '\0';
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	int				bd;
	char			buf[BUFFER_SIZE + 1];
	t_file			*tmp;	//nodo temporaneo
	static	t_file	*head;	//indirizzo di memoria primo nodo

	tmp = create_check(fd, &head);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !tmp)
		return (-1);
	while ((bd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bd] = '\0';
		tmp->content = ft_strjoin(tmp->content, buf);
		if (ft_strchr(buf, '\n'))
			break;
	}
	if (bd < 0)
		return (-1);
	if (bd == 0 && !(ft_strlen(tmp->content)))
		return (0);
	ft_cut(line, &(tmp->content));
	return (1);
}