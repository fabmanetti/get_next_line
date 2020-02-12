/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:46:30 by fmanetti          #+#    #+#             */
/*   Updated: 2020/02/06 18:04:30 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_file	*create_check(int fd, t_file **head)
{
	t_file	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (fd == tmp->fd)
		{
			if (tmp->content == NULL)
			{
				if (!(tmp->content = malloc(1)))
					return (NULL);
			}
			return (tmp);
		}
		tmp = tmp->next;
	}
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

static	void	ft_cut(char **line, char **str)
{
	int		x;
	char	*tmp;

	x = 0;
	if (ft_strchr(*str, '\n'))
	{
		while ((*str)[x] != '\n')
			x++;
		*line = ft_substr(*str, 0, x);
		tmp = ft_substr(*str, x, ft_strlen(*str) - x);
		free(*str);
		*str = ft_strdup(tmp);
		free(tmp);
	}
	else
	{
		x = ft_strlen(*str);
		*line = ft_substr(*str, 0, x);
		tmp = ft_substr(*str, x, ft_strlen(*str) - x);
		free(*str);
		*str = ft_strdup(tmp);
		free(tmp);
	}
}

static	void	giovanni(t_file **tmp)
{
	int x;

	x = 0;
	while (*tmp)
	{
		if ((*tmp)->content != NULL)
			x = 1;
		*tmp = (*tmp)->next;
	}
	if (x == 0)
		free(*tmp);
}

static int		fucking_space(char **line, t_file **tmp, int bd)
{
	char	*tmp2;

	ft_cut(line, &((*tmp)->content));
	if (*line == NULL)
	{
		if (!(*line = malloc(sizeof(char))))
			return (-1);
		(*line)[0] = '\0';
	}
	if (bd == 0 && ((*tmp)->content)[0] == '\0')
	{
		free((*tmp)->content);
		(*tmp)->content = NULL;
		giovanni(tmp);
		return (0);
	}
	tmp2 = ft_strdup((*tmp)->content);
	free((*tmp)->content);
	(*tmp)->content = ft_substr(tmp2, 1, ft_strlen(tmp2) - 1);
	free(tmp2);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	int				bd;
	char			*buf;
	t_file			*tmp;
	static	t_file	*head;
	char			*tmp2;

	tmp = create_check(fd, &head);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !tmp)
		return (-1);
	if (!(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	while ((bd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bd] = '\0';
		tmp2 = ft_strdup(tmp->content);
		free(tmp->content);
		tmp->content = ft_strjoin(tmp2, buf);
		free(tmp2);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (bd < 0)
		return (-1);
	free(buf);
	return (fucking_space(line, &tmp, bd));
}
