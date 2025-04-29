/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:47:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 00:44:51 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y] || !map[y][x]
		|| map[y][x] == '1' || map[y][x] == 'E')
		return ;
	if (map[y][x] == 'V')
		return ;
	map[y][x] = 'V';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	find_player_and_fill_map(char **map_copy, t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->ship_map[y][x] == 'P')
			{
				flood_fill(map_copy, (int)x, (int)y);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	check_valid_path(t_map *map)
{
	char	**map_copy;

	if (!clone_map_and_check(map, &map_copy))
		return (0);
	if (!find_player_and_fill_map(map_copy, map))
	{
		ft_free_matrix((void **)map_copy);
		return (0);
	}
	if (!check_reachable_items(map_copy, map))
	{
		ft_free_matrix((void **)map_copy);
		return (0);
	}
	ft_free_matrix((void **)map_copy);
	return (1);
}
