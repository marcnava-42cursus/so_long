/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:35:47 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 00:43:57 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**clone_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = ft_calloc(height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i-- > 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

int	clone_map_and_check(t_map *map, char ***map_copy)
{
	*map_copy = clone_map(map->ship_map, map->height);
	if (!(*map_copy))
	{
		ft_printf("Error: Failed to allocate memory for map check\n");
		return (0);
	}
	return (1);
}

int	check_reachable_items(char **map_copy, t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->ship_map[y][x])
		{
			if (map->ship_map[y][x] == 'C' && map_copy[y][x] != 'V')
				return (ft_printf("Error: Can't reach all elements\n"), 0);
			if (map->ship_map[y][x] == 'E')
			{
				if (!((y > 0 && map_copy[y - 1][x] == 'V')
					|| (y + 1 < map->height && map_copy[y + 1][x] == 'V')
					|| (x > 0 && map_copy[y][x - 1] == 'V')
					|| (map_copy[y][x + 1] == 'V')))
					return (ft_printf("Error: Exit is not accesible\n"), 0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
