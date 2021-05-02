/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:41:53 by fmanetti          #+#    #+#             */
/*   Updated: 2021/05/02 13:26:52 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ending(char *tmp, char *buf)
{
	if (tmp)
		free(tmp);
	if (buf)
		free(buf);
	return (-1);
}

static char		*ft_substr_nl(char *s, unsigned int start, size_t len)
{
	char	*tmp;

	tmp = ft_substr(s, start, len);
	free(s);
	return (tmp);
}

static void		ft_cut(char **line, char **tmp)
{
	int		x;

	x = 0;
	if (ft_strchr(*tmp, '\n'))
	{
		while ((*tmp)[x] != '\n')
			x++;
		*line = ft_substr(*tmp, 0, x);
		*tmp = ft_substr_nl(*tmp, x, ft_strlen(*tmp) - x);
	}
	else
	{
		*line = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
	}
}

static int		fucking_space(char **line, char **tmp, int bd)
{
	ft_cut(line, tmp);
	if (*line == NULL)
		if (!(*line = ft_strdup("")))
			return (ending(*tmp, NULL));
	if (bd == 0 && !(*tmp))
		return (0);
	*tmp = ft_substr_nl(*tmp, 1, ft_strlen(*tmp) - 1);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	int				bd;
	char			*buf;
	static char		*tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (!tmp)
		if (!(tmp = ft_strdup("")))
			return (-1);
	if (!(buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (ending(tmp, NULL));
	while ((bd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bd] = '\0';
		tmp = ft_strjoin_nl(tmp, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (bd < 0)
		return (ending(tmp, buf));
	free(buf);
	return (fucking_space(line, &tmp, bd));
}
