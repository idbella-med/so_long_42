#include "so_long.h"

static void	cleanup_exit(t_game **a, t_player **p, char *msg)
{
	free(*a);
	free(*p);
	error_exit(msg);
}

void ft_free(char **arr)
{
    int i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void load_exit(t_game *a, int c)
{
    if (c == 0)
        a->exit.img = mlx_xpm_file_to_image(a->mlx, "images/exit3.xpm", &a->exit.width, &a->exit.height);
    else
        a->exit.img = mlx_xpm_file_to_image(a->mlx, "images/exit2.xpm", &a->exit.width, &a->exit.height);
}

void move_player(t_game *a, int new_x, int new_y)
{
    if (new_x < 0 || new_x >= a->x || new_y < 0 || new_y >= a->y)
        return ;
    if (a->map[new_y][new_x] == '1')
        return ;
    if (a->map[new_y][new_x] == 'C')
    {
        a->collectibles_count--;
        a->map[new_y][new_x] = '0';
    }
    if (a->collectibles_count == 0)
        load_exit(a, a->collectibles_count);
    if (a->map[new_y][new_x] == 'E')
    {
       
        if (a->collectibles_count == 0)
        {
            ft_putstr_fd("You win!\n", 1);
            exit(0);
        }
        else
        {
            load_exit(a, a->collectibles_count);
            a->map[a->player->y][a->player->x] = '0';
            a->player->x = new_x;
            a->player->y = new_y;
        }
    }
    else if(a->map[a->player->y][a->player->x] == 'E')
    {
        load_images(a);
        a->map[a->player->y][a->player->x] = 'E';
        a->player->x = new_x;
        a->player->y = new_y;
        a->map[new_y][new_x] = 'P';
    }
    else
    {
        a->map[a->player->y][a->player->x] = '0';
        a->player->x = new_x;
        a->player->y = new_y;
        a->map[new_y][new_x] = 'P';
    }
    ft_putstr_fd("Moves: ", 1);
    ft_putnbr_fd(++a->moves_count, 1);
    ft_putchar_fd('\n', 1);
    render_map(a);
}


int handle_keypress(int keycode, t_game *a)
{
    int new_x = a->player->x;
    int new_y = a->player->y;

    if (keycode == 53)
        exit(0);
    else if (keycode == 13 || keycode == 126)
        new_y--;
    else if (keycode == 1 || keycode == 125)
        new_y++;
    else if (keycode == 0 || keycode == 123)
        new_x--;
    else if (keycode == 2 || keycode == 124)
        new_x++;
    else
        return 0;
    move_player(a, new_x, new_y);
    return (0);
}

static void	init_game(t_game **a, t_player **p, char *nmap)
{
	if (!(*a = malloc(sizeof(t_game))))
		error_exit("Memory allocation failed");
	ft_memset(*a, 0, sizeof(t_game));
	if (!(*p = malloc(sizeof(t_player))))
	{
		free(*a);
		error_exit("Memory allocation failed");
	}
	(*a)->player = *p;
	map(*a, nmap);
	search_for_player(*p, *a);
	if (!check_valid_path(*a, *p))
		cleanup_exit(a, p, "No valid path!");
	if (!((*a)->mlx = mlx_init()))
		cleanup_exit(a, p, "Failed to initialize MLX");
	if (!((*a)->windows = mlx_new_window((*a)->mlx, (*a)->x * size,
			(*a)->y * size, "so_long")))
	{
		free((*a)->mlx);
		cleanup_exit(a, p, "Failed to create window");
	}
	load_images(*a);
	render_map(*a);
}


int close_windows(t_game *a)
{
    if (a->windows)
        mlx_destroy_window(a->mlx, a->windows);
    ft_free(a->map);
    free(a->player);
    free(a);
    exit(0);
    return (0);
}

int	main(int ac, char **av)
{
	t_game	*a;
	t_player	*p;

	if (ac != 2)
		error_exit("Usage: ./so_long map.ber");
	init_game(&a, &p, av[1]);
    mlx_hook(a->windows, 17, 1, close_windows, a);
	mlx_hook(a->windows, 2, 1, handle_keypress, a);
	mlx_loop(a->mlx);
	// ft_free(a->map);
	// free(a);
	// free(p);
	return (0);
}

