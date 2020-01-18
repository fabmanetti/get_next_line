/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:41:53 by fmanetti          #+#    #+#             */
/*   Updated: 2020/01/18 17:50:47 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	int				x;
	int				bd;
	static char		buf[fd][BUFFER_SIZE + 1]

	while ((bd = read(fd, buf[fd], BUFFER_SIZE)) > 0)
	{
		
	}
	if (fd < 0 || line == NULL || BUFFER_SIZE < 0 || bd < 0)
		return (-1);
	return ()
}