/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:22:28 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:53:27 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	allocate_map_memory(t_map **map, char ***temp_map, size_t max_lines)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_printf("Error: Failed to allocate memory for map\n"),
			EXIT_FAILURE);
	*temp_map = ft_calloc(max_lines + 1, sizeof(char *));
	if (!*temp_map)
	{
		ft_free((void **)map);
		return (ft_printf("Error: Failed to allocate temp_map\n"),
			EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	allocate_baba_map_memory(t_map *map)
{
	size_t	y;
	size_t	width_to_use;

	width_to_use = map->width;
	if (width_to_use < 7)
		width_to_use = 7;
	map->baba_map = ft_calloc(7 + 1, sizeof(char *));
	if (!map->baba_map)
	{
		ft_printf("Error: Malloc baba_map failed\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < 7)
	{
		map->baba_map[y] = ft_calloc(width_to_use + 1, sizeof(char));
		if (!map->baba_map[y])
		{
			ft_printf("Error: Malloc baba_map row failed\n");
			exit(EXIT_FAILURE);
		}
		map->baba_map[y][width_to_use] = '\0';
		y++;
	}
	map->baba_map[7] = NULL;
}

int	load_temp_map(char *map_path, t_map **map,
			char ***temp_map, size_t *lines_read)
{
	int	status;
	int	fd;

	status = open_map_file(map_path, &fd);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = allocate_map_memory(map, temp_map, MAX_MAP_SIZE);
	if (status == EXIT_FAILURE)
	{
		close(fd);
		return (EXIT_FAILURE);
	}
	*lines_read = read_map_lines(fd, *temp_map);
	close(fd);
	return (EXIT_SUCCESS);
}

int	add_row(char **temp_map, char *line, size_t idx)
{
	char	*row;
	size_t	len;

	len = strip_newline(line);
	row = ft_calloc(MAX_MAP_SIZE, sizeof(char));
	if (!row)
	{
		ft_free((void **)&line);
		ft_free_matrix((void **)temp_map);
		return (EXIT_FAILURE);
	}
	ft_memcpy(row, line, len);
	ft_free((void **)&line);
	temp_map[idx] = row;
	return (EXIT_SUCCESS);
}

char	*read_next_non_empty_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		ft_free((void **)&line);
		line = get_next_line(fd);
	}
	return (line);
}
