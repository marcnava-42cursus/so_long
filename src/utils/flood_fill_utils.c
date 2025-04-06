/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:35:47 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 19:38:59 by marcnava         ###   ########.fr       */
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
	*map_copy = clone_map(map->map, map->height);
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
	size_t	found_c;
	size_t	found_e;

	found_c = 0;
	found_e = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C' && map_copy[y][x] != 'V')
				found_c = 1;
			if (map->map[y][x] == 'E' && map_copy[y][x] != 'V')
				found_e = 1;
			x++;
		}
		y++;
	}
	if (found_c || found_e)
		return (ft_printf(
				"Error: Not all collectibles or exit are reachable\n"), 0);
	return (1);
}
