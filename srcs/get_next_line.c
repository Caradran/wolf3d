/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:51:36 by esuits            #+#    #+#             */
/*   Updated: 2017/12/09 14:59:29 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_ralloc(char **str)
{
	char *res;

	res = ft_strdup(*str);
	ft_memdel((void**)str);
	if (!(*str = ft_strnew(ft_strlen(res) + BUFF_SIZE)))
		return (0);
	*str = ft_strcpy(*str, res);
	ft_memdel((void **)&res);
	return (1);
}

int		ft_endgnl(char **buffer, char **line)
{
	unsigned long long int	i;
	int						flag;

	i = -1;
	flag = 0;
	ft_memdel((void **)line);
	*line = ft_strdup(*buffer);
	ft_memdel((void **)buffer);
	while ((*line)[++i])
		if ((*line)[i] == '\n')
		{
			flag = 1;
			(*line)[i] = '\0';
			*buffer = ft_strdup(&((*line)[i + 1]));
			break ;
		}
	if (i && !flag)
	{
		ft_memdel((void **)buffer);
		*buffer = NULL;
		return (1);
	}
	return (1 && flag);
}

int		get_next_line(const int fd, char **line)
{
	static char				*buffer;
	long long int			j;

	if (fd < 0 || !line || !(*line = ft_strnew(BUFF_SIZE)))
		return (-1);
	if (!buffer)
		if (!(buffer = ft_strnew(BUFF_SIZE)))
			return (-1);
	while ((j = read(fd, *line, BUFF_SIZE)) > 0)
	{
		if (!(ft_ralloc(&buffer)))
			return (-1);
		buffer = ft_strncat(buffer, *line, j);
		if ((ft_strchr(buffer, '\n')))
			break ;
	}
	if (j == -1)
		return (-1);
	return (ft_endgnl(&buffer, line));
}
