/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:47:42 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:41:49 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".ber", 4));
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
