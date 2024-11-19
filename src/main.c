#include "../inc/map_checker.h"


int	main(int argc, char **argv)
{
	void	*mlx;
    void	*mlx_win;
    char **map;
    
    if (argc != 2)
        return (printf("Error\n"), 1);
    if (access(argv[1], F_OK | R_OK) == -1)
        return (printf("No such file or directory\n"), 1);
    map = create_map(count_file_lines(argv[1]), argv[1]);
    //print the map
    printf("the map prototype\n");
    for (int i = 0; map[i]; i++)
    {
        printf("%s\n", map[i]);
    }
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, get_map_weight(map) * 30, get_map_height(map) * 30, "PixelFlood");
    render_wall(map, mlx_win, mlx);
    render_floor(map, mlx_win, mlx);
    flood_fill(map, get_player_x(map), get_player_y(map), get_map_height(map), get_map_weight(map), (param){mlx, mlx_win});
    mlx_loop(mlx);
}