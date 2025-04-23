#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

# define BUFFER_SIZE	1024

# define KEY_W        119
# define KEY_A        97
# define KEY_S        115
# define KEY_D        100
# define KEY_UP       65362
# define KEY_DOWN     65364
# define KEY_LEFT     65361
# define KEY_RIGHT    65363
# define KEY_ESC      65307

typedef struct s_mlxgame
{
	void	*mlx;
	void	*window;
	void	*asset;
	char	**map;
	int		width;
	int		height;
	int		collectable_count;
	void	*floor;
	void	*player;
	void	*collectable;
	void	*wall;
	void	*exit;
	int		player_exit;
	int		move_count;
	int		player_x;
	int		player_y;
}	t_mlxgame;

bool	is_map_valid(char *mapstring);
char	*read_file(const char *filename);
int		checkfile_extension(char *filename);
int		is_rectangular(char *mapstring);
bool	playable_characters(char *mapstring);
bool	surrounded_by_walls(char *mapstring, int width);
void	flood_fill_recursive(char **map, int x, int y);
void	find_player(char **map, int *px, int *py);
void	free_map(char **map);
bool	flood_fill(char *mapstring);
bool	final_flood_check(char **maparray);
void	initialize_game(t_mlxgame *game);
void	load_assets(t_mlxgame *game);
void	load_render_map(t_mlxgame *game);
void	free_maparray(char **maparray);
int		handle_keys(int keycode, t_mlxgame *game);
int		move_player(t_mlxgame *game, int dx, int dy);
void	count_elements(t_mlxgame *game, char **map, char element);
int		close_game(t_mlxgame *game);

#endif
