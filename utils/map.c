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
	int	i;
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

void	check_newline(char *str)
{
	int	i;

	i = 0;
	if(str[0] == '\n')
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

static void	init_map(t_game *a, int len, char *map)
{
	int		fd;
	char	*tmp;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		error_exit("Error opening map file");
	tmp = ft_strdup("");
	if (!tmp)
		error_exit("Memory allocation failed");
	a->map = malloc(sizeof(char *) * (len + 1));
	if (!a->map)
		error_exit("Memory allocation failed");
	read_map(fd, &tmp);
	check_newline(tmp);
	a->map = ft_split(tmp, '\n');
	free(tmp);
	if (!a->map)
		error_exit("Memory allocation failed for map");
	close(fd);
}

void map(t_game *a, char *file_name)
{
    int len;
    char *map;

    len = count_line(file_name);
    map = file_name;
    file_name = file_name + (ft_strlen(file_name) - 4);
	if (ft_strncmp(file_name, ".ber", 4))
		error_exit("Error opening map file");
    if(!a)
        return;
    init_map(a, len, map);
	if (ft_strlen(a->map[0]) - 1 >= 50 || len >= 27)
		error_exit("Invalid map !");
    if (!a->map)
        error_exit("Failed to load map");
    init_struct(a, map);
    parsing_map(a);
	// puts("1");
    check_first_last(a, len);
}
