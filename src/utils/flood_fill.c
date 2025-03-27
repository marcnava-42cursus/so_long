/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:47:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/27 18:39:59 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void flood_fill(char **map, int x, int y)
{
	// Si está fuera del mapa o en una pared ('1'), no seguir
	if (x < 0 || y < 0 || !map[y] || !map[y][x] || map[y][x] == '1')
		return ;
	
	// Si ya fue visitado, no seguir
	if (map[y][x] == 'V')
		return ;
	
	// Marcar como visitado
	map[y][x] = 'V';

	// Llamadas recursivas en las 4 direcciones
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static char	**clone_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = ft_calloc(height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]); // Duplicar cada fila
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

int check_valid_path(t_map *map)
{
	char	**map_copy;
	size_t	y, x;
	size_t	found_c = 0, found_e = 0;

	map_copy = clone_map(map->map, map->height);
	if (!map_copy)
		return (ft_printf("Error\nFailed to allocate memory for map check\n"), 0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'P')
			{
				flood_fill(map_copy, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	// Revisar si quedan 'C' o 'E' sin alcanzar
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
	y = 0;
	ft_free_matrix((void **)map_copy);
	if (found_c || found_e)
		return (ft_printf("Error\nNot all collectibles or exit are reachable\n"), 0);
	return (1);
}
