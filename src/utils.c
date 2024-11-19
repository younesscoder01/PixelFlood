#include "../inc/map_checker.h"

size_t get_map_weight(char **map_name)
{
    return (strlen(map_name[0]));
}

size_t get_map_height(char **map_name)
{
    int i;
    
    i = 0;
    while (map_name[i])
        i++;
    return (i);
}

char **create_map(int h, char *file_name)
{
    int fd;
    char *line;
    int i;
    char **map;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (NULL);
    map = malloc(sizeof(char *) * (h));
    line = get_next_line(fd);
    i = 0;
    while (line)
    {
        map[i] = line;
        if (map[i][strlen(map[i]) - 1] == '\n')
            map[i][strlen(map[i]) - 1] = 0;
        if (map[i][0] == 0)
            map[i] = NULL;
        i++;
        line = get_next_line(fd);
    }
    map[i] = NULL;
    return map;
}

void render_30(void *mlx, void *mlx_win, int x, int y, int color)
{
    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            if (i == 0 || j == 0 || i == 29 || j == 29)
                mlx_pixel_put(mlx, mlx_win, x + j, y + i, 0x00000000);
            else
                mlx_pixel_put(mlx, mlx_win, x + j, y + i, color);
        }
    }
}

void render_wall(char **map,void *mlx_win, void	*mlx)
{
    int x;
    int y;

    x = 0;
    y = 0;
    for (int i = 0; map[i]; i++)
    {
        x = 0;
        for (int j = 0; map[i][j]; j++)
        {
            if ( map[i][j] == '1')
                render_30(mlx, mlx_win, x, y, 0x00FF0000);
            x += 30;
        }
        y += 30;
    }
}
void render_floor(char **map,void *mlx_win, void	*mlx)
{
    int x;
    int y;

    x = 0;
    y = 0;
    for (int i = 0; map[i]; i++)
    {
        x = 0;
        for (int j = 0; map[i][j]; j++)
        {
            if ( map[i][j] == '0')
                render_30(mlx, mlx_win, x, y, 0x00FFFFFF);
            x += 30;
        }
        y += 30;
    }
}

void render_d(char **map,void *mlx_win, void	*mlx)
{
    int x;
    int y;

    x = 0;
    y = 0;
    for (int i = 0; map[i]; i++)
    {
        x = 0;
        for (int j = 0; map[i][j]; j++)
        {
            if ( map[i][j] == 'D')
                render_30(mlx, mlx_win, x, y, 0x0000FF00);
            x += 30;
        }
        y += 30;
    }
}

void flood_fill(char **map, int x, int y, int h, int w, param par)
{
    if (x < 0 || y < 0 || y > h || x > w || map[y][x] == '1' || map[y][x] == 'D')
        return ;
    render_30(par.mlx, par.mlx_win, x* 30, y* 30, 0x000000FF);
    if (map[y][x] == 'P' || map[y][x] == '0')
        map[y][x] = 'D';
    usleep(1000 * 300);
    render_d(map, par.mlx_win, par.mlx);
    usleep(1000 * 200);
    flood_fill(map, x+1, y, h, w, par);
    flood_fill(map, x-1, y, h, w, par);
    flood_fill(map, x, y+1, h, w, par);
    flood_fill(map, x, y-1, h, w, par);
}

int count_file_lines(char *file_name)
{
    int fd;
    char *line;
    int i;

    fd = open(file_name, O_RDONLY);
    if (fd < 0)
        return (0);
    i = 0;
    line = get_next_line(fd);
    while (line)
    {
        i++;
        // if (line != NULL && line[0] == '\n')
        //     return i;
        line = get_next_line(fd);
    }
    return (i);
}

int get_player_x(char **map)
{
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == 'P')
                return j;
        }
    }
    return 1;
}

int get_player_y(char **map)
{
    for (int i = 0; map[i]; i++)
    {
        for (int j = 0; map[i][j]; j++)
        {
            if (map[i][j] == 'P')
                return i;
        }
    }
    return 1;
}