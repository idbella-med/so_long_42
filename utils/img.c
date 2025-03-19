/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohidbel <mohidbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:01:51 by mohidbel          #+#    #+#             */
/*   Updated: 2025/03/13 22:08:53 by mohidbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	load(void *mlx, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
}

static int	validate_images(t_game *a)
{
	return (a->wall.img && a->floor.img && a->player_img.img
		&& a->collectible.img && a->exit.img);
}

void	load_images(t_game *a)
{
	load(a->mlx, &a->wall, "images/wall.xpm");
	load(a->mlx, &a->floor, "images/floor.xpm");
	load(a->mlx, &a->player_img, "images/player.xpm");
	load(a->mlx, &a->collectible, "images/collectible.xpm");
	load(a->mlx, &a->exit, "images/exit.xpm");
	if (!validate_images(a))
		error_exit("Failed to load images");
}

static t_img	*get_tile_image(t_game *a, char tile)
{
	if (tile == '1')
		return (&a->wall);
	if (tile == '0')
		return (&a->floor);
	if (tile == 'P')
		return (&a->player_img);
	if (tile == 'C')
		return (&a->collectible);
	if (tile == 'E')
		return (&a->exit);
	return (NULL);
}

void	render_map(t_game *a)
{
	int		i;
	int		j;
	t_img	*img;

	i = -1;
	while (++i < a->y)
	{
		j = -1;
		while (++j < a->x)
		{
			img = get_tile_image(a, a->map[i][j]);
			if (img)
				mlx_put_image_to_window(a->mlx, a->windows,
					img->img, j * SIZE, i * SIZE);
		}
	}
}
