/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_io_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:45:34 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 22:23:56 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	read_map_lines(int fd, char **temp_map)
{
	char	*line;
	size_t	lines_read;
	int		status;

	lines_read = 0;
	line = get_next_line(fd);
	while (line)
	{
		status = add_row(temp_map, line, lines_read);
		if (status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		lines_read++;
		line = get_next_line(fd);
	}
	if (lines_read == 0)
	{
		ft_printf("Error: Map file is empty\n");
		return (EXIT_FAILURE);
	}
	return ((int)lines_read);
}

int	finalize_map(t_game *game, t_map *map, char **temp_map, size_t lines_read)
{
	map->ship_map = temp_map;
	temp_map[lines_read] = NULL;
	map->height = lines_read;
	map->width = ft_strlen(temp_map[0]);
	allocate_baba_map_memory(map);
	if (!validate_map(map))
	{
		ft_free_matrix((void **)map->ship_map);
		ft_free((void **)&map);
		return (EXIT_FAILURE);
	}
	game->map = map;
	return (EXIT_SUCCESS);
}
