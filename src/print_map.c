/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:29:47 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/29 20:49:08 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	print_map(t_map *map)
{
	size_t	i;
	size_t	j;

	if (!map || !map->map)
	{
		ft_printf("Error\nMap is not initialized\n");
		return ;
	}
	i = 0;
	while (i < map->height)
	{
		ft_printf("[");
		j = 0;
		while (j < map->width)
		{
			ft_printf("%c", map->map[i][j]);
			if (j < map->width - 1)
				ft_printf(",");
			j++;
		}
		ft_printf("],\n");
		i++;
	}
}
