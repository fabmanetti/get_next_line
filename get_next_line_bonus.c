/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:41:53 by fmanetti          #+#    #+#             */
/*   Updated: 2020/01/29 12:42:48 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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

static	void		ft_cut(char **line, char **str)
{
	int		x;

	x = 0;
	if (ft_strchr(*str, '\n'))
	{
		while ((*str)[x] != '\n')
			x++;
		*line = ft_substr(*str, 0, x);
		//*str = *str + x + 1; 
	}
	else
	{
		x = ft_strlen(*str);
		*line = ft_substr(*str, 0, x);
		//*str = *str + x;
	}
}

static	void	advance(char **str)
{
	int		x;

	x = 0;
	if (ft_strchr(*str, '\n'))
	{
		while ((*str)[x] != '\n')
			x++;
		*str = *str + x; 
	}
	else
	{
		x = ft_strlen(*str);
		*str = *str + x;
	}
}

int		get_next_line(int fd, char **line)
{
	int				bd;
	char			buf[BUFFER_SIZE + 1];
	t_file			*tmp;	//nodo temporaneo
	static	t_file	*head;	//indirizzo di memoria primo nodo

	tmp = create_check(fd, &head);
	if (fd < 0 || !line || BUFFER_SIZE < 1 || !tmp) // errori 1
		return (-1);
	while ((bd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bd] = '\0';
		tmp->content = ft_strjoin(tmp->content, buf);
		if (ft_strchr(buf, '\n'))
			break;
	}
	if (bd < 0)									//errori 2
		return (-1);
	ft_cut(line, &(tmp->content));
	if (*line == NULL)
	{
		if (!(*line = malloc(sizeof(char))))
			return (-1);
		(*line)[0] = '\0';
	}
	advance(&(tmp->content));
	if (bd == 0 && (tmp->content)[0] == '\0')
		return (0);
	tmp->content++;
	return (1);
}

//  int		main(int argc, char **argv)
//   {
//   	char *ciao;
//   	int fd;

//   	ciao = NULL;
//  	argc = 2;
//   	fd = open(argv[1], O_RDONLY);
//   	while (get_next_line(fd, &ciao) > 0) 
//  		printf("|%s\n", ciao);
// 	printf("|%s\n", ciao);
//  	while(1)
//   	return (0);
//   }