/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alschnei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:32:16 by alschnei          #+#    #+#             */
/*   Updated: 2025/03/24 14:32:17 by alschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	initialize_mlx(char *filecontent)
{
	t_mlxgame	game;
	int			height;

	game.map = ft_split(filecontent, '\n');
	if (!game.map)
		return (free(filecontent), write(1, "Map Creation Error", 18), 0);
	game.width = is_rectangular(filecontent);
	height = 0;
	free(filecontent);
	while (game.map[height])
		game.height = ++height;
	initialize_game(&game);
	load_assets(&game);
	load_render_map(&game);
	mlx_loop(game.mlx);
	return (1);
}

int	checkfile_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename) - 4;
	if (ft_strcmp(filename + len, ".ber") == 1)
		return (1);
	else
		return (0);
}

char	*read_file(const char *filename)
{
	char		*buffer;
	int			fd;
	int			len;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	len = read(fd, buffer, BUFFER_SIZE);
	if (len < 1)
		return (free(buffer), NULL);
	buffer[len] = '\0';
	close(fd);
	return (buffer);
}

int	main(int argc, char **argv)
{
	char		*filecontent;

	if (argc == 2 && checkfile_extension(argv[1]))
	{
		filecontent = read_file(argv[1]);
		if (!filecontent)
			return (write(1, "Invalid file", 12), 1);
		if (!is_map_valid(filecontent))
			return (free(filecontent), 1);
	}
	else
		return (write(1, "Invalid extension | Check arguments", 35), 1);
	initialize_mlx(filecontent);
	printf("Content:\n%s", filecontent);
	return (0);
}
