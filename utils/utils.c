/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:24 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 22:07:00 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	count_line(char *map)
{
	int		fd;
	int		count;
	char	*str;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening map file");
	count = 0;
	str = get_next_line(fd);
	while (str)
	{
		count++;
		free(str);
		str = get_next_line(fd);
	}
	if (close(fd) == -1)
		error_exit("Error closing file");
	return (count);
}

void	error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

void	check_newline(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
		error_exit("Invalid map !");
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			error_exit("Invalid map !");
		i++;
	}
	if (str[i - 1] == '\n')
		error_exit("Invalid map !");
}

void	ft_free(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	load_exit(t_game *a, int c)
{
	if (c == 0)
		a->exit.img = mlx_xpm_file_to_image(a->mlx,
				"images/exit3.xpm", &a->exit.width, &a->exit.height);
	else
		a->exit.img = mlx_xpm_file_to_image(a->mlx,
				"images/exit2.xpm", &a->exit.width, &a->exit.height);
}
