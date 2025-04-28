/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 21:10:53 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 21:11:23 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".ber", 4));
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'P' || c == 'C' || c == 'E');
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
			if (!is_valid_char(map->ship_map[i][j]))
				return (ft_printf("Error: Invalid character in map: %c\n",
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
