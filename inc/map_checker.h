#ifndef MAP_CHECKER_H
# define MAP_CHECKER_H
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>
#include "get_next_line.h"
#include <stdlib.h>
typedef struct 
{
    void	*mlx;
    void	*mlx_win;

} param;

int get_player_y(char **map);
int get_player_x(char **map);
int count_file_lines(char *file_name);
void flood_fill(char **map, int x, int y, int h, int w, param par);
void render_d(char **map, void *mlx_win, void *mlx);
void render_floor(char **map, void *mlx_win, void *mlx);
void render_wall(char **map, void *mlx_win, void *mlx);
void render_30(void *mlx, void *mlx_win, int x, int y, int color);
size_t get_map_height(char **map);
size_t get_map_weight(char **map);
char **create_map(int lines, char *file_name);

#endif