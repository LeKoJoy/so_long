#include "includes/so_long.h"

int	handle_keys(int keycode, t_mlxgame *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	else if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	return (load_render_map(game), 0);
}

int	move_player(t_mlxgame *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == '1')
		return (0);
	if (game->map[new_y][new_x] == 'E' && game->collectable_count > 0)
		game->player_exit = 0;
	if (game->map[new_y][new_x] == 'C')
	{
		game->collectable_count--;
		game->map[new_y][new_x] = '0';
	}
	if (game->map[new_y][new_x] == 'E' && game->collectable_count == 0)
		(write(1, "🎉 You won! Closing game...\n", 30), close_game(game));
	if (game->player_exit == 0 && game->map[new_y][new_x] == '0')
	{
		game->map[game->player_y][game->player_x] = 'E';
		game->player_exit = 1;
	}
	else
		game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	return (game->player_x = new_x, game->player_y = new_y, 0);
}

int	close_game(t_mlxgame *game)
{
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collectable)
		mlx_destroy_image(game->mlx, game->collectable);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_maparray(game->map);
	exit(0);
}
