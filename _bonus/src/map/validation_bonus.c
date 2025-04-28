/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:25:24 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 22:05:56 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_min_width(t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	old_width;

	if (map->width >= 7)
		return (1);
	old_width = map->width;
	map->width = 7;
	i = 0;
	while (i < map->height)
	{
		j = old_width;
		while (j < 7)
		{
			map->ship_map[i][j] = '0';
			j++;
		}
		map->ship_map[i][j] = '\0';
		i++;
	}
	return (1);
}

int	validate_map(t_map *map)
{
	int	p_count;
	int	e_count;
	int	c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	if (!check_row_widths(map))
		return (ft_printf("Error: Different width sizes"), 0);
	if (!count_elements(map, &p_count, &e_count, &c_count))
		return (ft_printf("Error: Invalid character in map\n"), 0);
	if (map_errors(p_count, c_count, e_count))
		return (ft_printf("Error: Invalid number of elements\n"), 0);
	if (!check_walls(map))
		return (ft_printf("Error: Map is not surrounded by walls\n"), 0);
	if (!check_valid_path(map))
		return (ft_printf(
			"Error: Not all collectibles or exit are reachable\n"), 0);
	if (!check_min_width(map))
		return (ft_printf("Error: Cannot add extra chars to map\n"), 0);
	return (1);
}

int	check_row_widths(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		if (ft_strlen(map->ship_map[i]) != map->width)
		{
			ft_printf("Error: Map rows must have the same width\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_walls(t_map *map)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < map->width)
	{
		if (map->ship_map[0][j] != '1'
			|| map->ship_map[map->height - 1][j] != '1')
			return (ft_printf("Error: Map must be enclosed by walls (1)\n"), 0);
		j++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->ship_map[i][0] != '1'
			|| map->ship_map[i][map->width - 1] != '1')
		{
			ft_printf("Error: Map must be enclosed by walls (1) at sides\n");
			return (0);
		}
		i++;
	}
	return (1);
}
