/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:41:53 by fmanetti          #+#    #+#             */
/*   Updated: 2022/04/23 19:49:20 by fmanetti         ###   ########.fr       */
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

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
