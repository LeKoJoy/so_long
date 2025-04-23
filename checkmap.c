/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alschnei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:59:14 by alschnei          #+#    #+#             */
/*   Updated: 2025/03/26 14:59:17 by alschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	is_rectangular(char *mapstring)
{
	int	i;
	int	width;
	int	row_length;
	int	height;

	i = 0;
	width = 0;
	row_length = 0;
	height = 0;
	while (mapstring[i] && mapstring[i++] != '\n')
		width++;
	i = 0;
	while (mapstring[i])
	{
		if (mapstring[i++] == '\n')
		{
			if (row_length != width)
				return (0);
			row_length = 0;
			height++;
		}
		else
			row_length++;
	}
	return (width);
}

bool	playable_characters(char *mapstring)
{
	int	i;
	int	player_count;
	int	exit_count;
	int	collectible_count;

	i = 0;
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	while (mapstring[i])
	{
		if (mapstring[i] == 'P')
			player_count++;
		else if (mapstring[i] == 'E')
			exit_count++;
		else if (mapstring[i] == 'C')
			collectible_count++;
		else if (mapstring[i] != '0' && mapstring[i] != '1'
			&& mapstring[i] != '\n')
			return (write(1, "Map: Check playable characters", 30), false);
		i++;
	}
	if (player_count != 1 || exit_count != 1 || collectible_count < 1)
		return (write(1, "Map: Check playable characters", 30), false);
	return (true);
}
/*
bool	surrounded_by_walls(char *mapstring, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		if (mapstring[i] != '1'
			|| mapstring[ft_strlen(mapstring) - width - 1 + i] != '1')
			return (write(1, "Map: Not surrounded by walls", 28), false);
		i++;
	}
	i = 0;
	while (mapstring[i])
	{
		if (i % (width + 1) == 0 || i % (width + 1) == width - 1)
		{
			if (mapstring[i] != '1')
				return (write(1, "Map: Not surrounded by walls", 28), false);
		}
		i++;
	}
	return (true);
}
*/

bool	surrounded_by_walls(char *mapstring, int width)
{
	int		i;
	size_t	map_len;
	size_t	last_row_start;

	map_len = ft_strlen(mapstring);
	if (mapstring[map_len - 1] == '\n')
		map_len--;
	last_row_start = map_len - width;
	i = -1;
	while (++i < width)
		if (mapstring[i] != '1' || mapstring[last_row_start + i] != '1')
			return (write(1, "Map: Not surrounded by walls\n", 30), false);
	i = -1;
	while (mapstring[++i])
	{
		if (mapstring[i] == '\n')
			continue ;
		if (i % (width + 1) == 0 || i % (width + 1) == width - 1)
			if (mapstring[i] != '1')
				return (write(1, "Map: Not surrounded by walls\n", 30), false);
	}
	return (true);
}

bool	is_map_valid(char *mapstring)
{
	int	width;

	width = is_rectangular(mapstring);
	if (width < 3)
		return (write(1, "Map not rectangular", 19), false);
	else if (!playable_characters(mapstring))
		return (false);
	else if (!surrounded_by_walls(mapstring, width))
		return (false);
	else if (!flood_fill(mapstring))
		return (false);
	return (true);
}
