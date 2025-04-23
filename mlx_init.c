/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alschnei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:32:16 by alschnei          #+#    #+#             */
/*   Updated: 2025/03/24 14:32:17 by alschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	count_elements(t_mlxgame *game, char **map, char element)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	game->collectable_count = 0;
	while (map[x])
	{
		while (map[x][y])
		{
			if (map[x][y] == element)
				game->collectable_count++;
			y++;
		}
		x++;
		y = 0;
	}
}

void	initialize_game(t_mlxgame *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error: MLX init failed\n", 23);
		free_maparray(game->map);
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, game->width * 50,
			game->height * 50, "so_long");
	if (!game->window)
	{
		write(2, "Error: Window creation failed\n", 30);
		free_maparray(game->map);
		exit(1);
	}
	game->move_count = 0;
	count_elements(game, game->map, 'C');
	find_player(game->map, &game->player_x, &game->player_y);
	game->player_exit = 1;
	mlx_hook(game->window, 2, 1L << 0, handle_keys, game);
	mlx_hook(game->window, 17, 1L << 0, close_game, game);
	mlx_hook(game->window, 17, 0, close_game, game);
}

void	load_assets(t_mlxgame *game)
{
	int	w;
	int	h;

	game->wall = mlx_xpm_file_to_image(game->mlx, "assets/Wall.xpm", &w, &h);
	game->floor = mlx_xpm_file_to_image(game->mlx, "assets/Floor.xpm", &w, &h);
	game->player = mlx_xpm_file_to_image(game->mlx,
			"assets/Player.xpm", &w, &h);
	game->collectable = mlx_xpm_file_to_image(game->mlx,
			"assets/Collectable.xpm", &w, &h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "assets/Exit.xpm", &w, &h);
	if (!game->wall || !game->floor || !game->player
		|| !game->collectable || !game->exit)
	{
		write(1, "Error: Failed to load assets\n", 29);
		close_game(game);
	}
}

void	load_render_map(t_mlxgame *game)
{
	int		x;
	int		y;
	void	*img;

	y = -1;
	printf("Moves: %d\n", game->move_count++);
	while (game->map[++y])
	{
		x = 0;
		while (game->map[y][x])
		{
			img = game->floor;
			if (game->map[y][x] == '1')
				img = game->wall;
			else if (game->map[y][x] == 'P')
				img = game->player;
			else if (game->map[y][x] == 'C')
				img = game->collectable;
			else if (game->map[y][x] == 'E')
				img = game->exit;
			mlx_put_image_to_window(game->mlx, game->window,
				img, x * 50, y * 50);
			x++;
		}
	}
}

void	free_maparray(char **maparray)
{
	int	i;

	i = 0;
	while (maparray[i])
	{
		free(maparray[i]);
		i++;
	}
	free(maparray);
}
