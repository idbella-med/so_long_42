#include "../so_long.h"

void    search_for_player(t_player *a, t_game *s)
{
    int i;
    int j;

    i = 0;
    while (s->map[i])
    {
        j = 0;
        while(s->map[i][j])
        {
            if (s->map[i][j] == 'P')
            {
                a->x = j;
                a->y = i;
            }
            else if (s->map[i][j] == 'C')
                s->collectibles_count++;
            j++;
        }
        i++;
    }
}


int count_line(char *map)
{
    int fd;
    int count;
    char *str;

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
    close(fd);
    return(count);
}

static void	fill(char **tab, int x, int y)
{
	if (tab[y][x] == '1' || tab[y][x] == 'F' || tab[y][x] == '\0' || tab[y] == NULL)
		return ;
	tab[y][x] = 'F';
	fill(tab, x - 1, y);
	fill(tab, x + 1, y);
	fill(tab, x, y - 1);
	fill(tab, x, y + 1);
}

int check_valid_path(t_game *a, t_player *player)
{
    int i;
    int j;
    char **copy;

    i = -1;
    copy = malloc(sizeof(char *) * (a->y + 1));
    if (!copy)
        return (0);
    while (++i < a->y)
    {
        copy[i] = ft_strdup(a->map[i]);
        if (!copy[i])
            return (ft_free(copy), 0);
    }
    copy[i] = NULL;
    fill(copy, player->x, player->y);
    i = -1;
    while (++i < a->y)
    {
        j = -1;
        while (j++ < a->x)
            if ((a->map[i][j] == 'C' || a->map[i][j] == 'E') && copy[i][j] != 'F')
                return (ft_free(copy), 0);
    }
    return (ft_free(copy), 1);
}

void init_struct(t_game *a, char *map)
{
    if (a->map && a->map[0])
        a->x = ft_strlen(a->map[0]);
    a->y = count_line(map);
    a->collectibles_count = 0;
    a->moves_count = 0;
}

void error_exit(const char *msg)
{
    perror(msg);
    exit(1);
}
