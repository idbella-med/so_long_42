#include "../so_long.h"

void load_images(t_game *a)
{
    a->wall.img = mlx_xpm_file_to_image(a->mlx, "images/wall.xpm", &a->wall.width, &a->wall.height);
    a->floor.img = mlx_xpm_file_to_image(a->mlx, "images/floor.xpm", &a->floor.width, &a->floor.height);
    a->player_img.img = mlx_xpm_file_to_image(a->mlx, "images/player.xpm", &a->player_img.width, &a->player_img.height);
    a->collectible.img = mlx_xpm_file_to_image(a->mlx, "images/collectible.xpm", &a->collectible.width, &a->collectible.height);
    a->exit.img = mlx_xpm_file_to_image(a->mlx, "images/exit.xpm", &a->exit.width, &a->exit.height);
    if (!a->wall.img || !a->floor.img || !a->player_img.img || !a->collectible.img || !a->exit.img)
        error_exit("Failed to load images");
}

void render_map(t_game *a)
{
    int i = 0;
    int j;

    while (i < a->y)
    {
        j = 0;
        while (j < a->x)
        {
            if (a->map[i][j] == '1')
                mlx_put_image_to_window(a->mlx, a->windows, a->wall.img, j * size, i * size);
            else if (a->map[i][j] == '0')
                mlx_put_image_to_window(a->mlx, a->windows, a->floor.img, j * size, i * size);
            else if (a->map[i][j] == 'P')
                mlx_put_image_to_window(a->mlx, a->windows, a->player_img.img, j * size, i * size);
            else if (a->map[i][j] == 'C')
                mlx_put_image_to_window(a->mlx, a->windows, a->collectible.img, j * size, i * size);
            else if (a->map[i][j] == 'E')
                mlx_put_image_to_window(a->mlx, a->windows, a->exit.img, j * size, i * size);
            j++;
        }
        i++;
    }
}
