/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:15:02 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 21:48:56 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".ber", 4));
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

int	count_elements(t_map *map, int *p_count, int *e_count, int *c_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!ft_isprint(map->ship_map[i][j]))
				return (ft_printf("Error: Invalid character in map: %d\n",
						map->ship_map[i][j]), 0);
			if (map->ship_map[i][j] == 'P')
				(*p_count)++;
			if (map->ship_map[i][j] == 'E')
				(*e_count)++;
			if (map->ship_map[i][j] == 'C')
				(*c_count)++;
			j++;
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
