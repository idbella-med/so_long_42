/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:11:20 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/09 00:06:28 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_line(char *save, int fd)
{
	char	*buff;
	ssize_t	redbyt;

	redbyt = 1;
	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_strchr(save, '\n') && redbyt > 0)
	{
		redbyt = read(fd, buff, BUFFER_SIZE);
		if (redbyt < 0)
		{
			if (save)
				free(save);
			return (free(buff), NULL);
		}
		if (redbyt == 0)
			break ;
		buff[redbyt] = '\0';
		save = ft_join(save, buff);
	}
	free(buff);
	return (save);
}

static char	*ft_get_line(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (free(save), NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*ft_get_next(char *save)
{
	char	*next;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!ft_strchr(save, '\n'))
		return (free(save), NULL);
	while (save[i])
		i++;
	while (save[j] != '\n')
		j++;
	next = malloc((i - j) * sizeof(char));
	if (!next)
		return (free(save), NULL);
	j++;
	i = 0;
	while (save[j])
		next[i++] = save[j++];
	next[i] = '\0';
	free(save);
	if (!next[0])
		return (free(next), NULL);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = ft_read_line(save, fd);
	if (!save)
		return (NULL);
	line = ft_get_line(save);
	save = ft_get_next(save);
	return (line);
}
