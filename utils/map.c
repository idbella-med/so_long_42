/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:46 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 21:48:13 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	check_horizontal_walls(t_game *a, int row, char *msg)
{
	int	j;

	j = 0;
	while (a->map[row][j])
	{
		if (a->map[row][j] != '1')
			error_exit(msg);
		j++;
	}
}

void	check_first_last(t_game *a, int len)
{
	int		i;
	size_t	len_line;

	len_line = ft_strlen(a->map[0]);
	check_horizontal_walls(a, 0, "Invalid map: Top wall incomplete");
	check_horizontal_walls(a, len - 1, "Invalid map: Bottom wall incomplete");
	if (ft_strlen(a->map[len - 1]) != len_line)
		error_exit("Invalid map: Bottom wall length mismatch");
	i = 0;
	while (++i < len - 1)
		if (ft_strlen(a->map[i]) != len_line)
			error_exit("Invalid map: Line lengths are not equal");
}

static void	read_map(int fd, char **tmp)
{
	char	*str;
	char	*s;

	str = get_next_line(fd);
	while (str)
	{
		s = ft_strjoin(*tmp, str);
		if (!s)
			error_exit("Memory allocation failed");
		free(*tmp);
		*tmp = s;
		free(str);
		str = get_next_line(fd);
	}
}

static void	init_map(t_game *a, char *map)
{
	int		fd;
	char	*tmp;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening map file");
	tmp = ft_strdup("");
	if (!tmp)
	{
		close(fd);
		error_exit("Memory allocation failed");
	}
	read_map(fd, &tmp);
	check_newline(tmp);
	a->map = ft_split(tmp, '\n');
	free(tmp);
	if (!a->map)
	{
		close(fd);
		error_exit("Memory allocation failed for map");
	}
	if (close(fd) == -1)
		error_exit("Error closing file");
}

void	map(t_game *a, char *file_name)
{
	int		len;
	char	*map;

	len = count_line(file_name);
	map = file_name;
	file_name = file_name + (ft_strlen(file_name) - 4);
	if (ft_strncmp(file_name, ".ber", 4))
		error_exit("Error opening map file");
	if (!a)
		return ;
	init_map(a, map);
	if (!a->map[0])
		error_exit("Failed to load map");
	if (ft_strlen(a->map[0]) - 1 >= 50 || len >= 27)
		error_exit("Invalid map !");
	if (!a->map)
		error_exit("Failed to load map");
	init_struct(a, map);
	parsing_map(a);
	check_first_last(a, len);
}
