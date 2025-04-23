/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flood_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alschnei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:58:34 by alschnei          #+#    #+#             */
/*   Updated: 2025/03/26 14:58:43 by alschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	flood_fill_recursive(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill_recursive(map, x + 1, y);
	flood_fill_recursive(map, x - 1, y);
	flood_fill_recursive(map, x, y + 1);
	flood_fill_recursive(map, x, y - 1);
}

void	find_player(char **map, int *px, int *py)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				*px = x;
				*py = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

bool	final_flood_check(char **maparray)
{
	int	i;
	int	j;

	i = 0;
	while (maparray[i])
	{
		j = 0;
		while (maparray[i][j])
		{
			if (maparray[i][j] == 'C' || maparray[i][j] == 'E')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	flood_fill(char *mapstring)
{
	int		x;
	int		y;
	char	**maparray;

	x = 0;
	y = 0;
	maparray = ft_split(mapstring, '\n');
	if (!maparray)
		return (write(1, "Map not playable", 16), false);
	find_player(maparray, &x, &y);
	flood_fill_recursive(maparray, x, y);
	if (!final_flood_check(maparray))
		return (free_map(maparray), write(1, "Map not playable", 16), false);
	free_map(maparray);
	return (true);
}
