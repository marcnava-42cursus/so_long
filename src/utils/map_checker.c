/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:15:02 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 00:46:26 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		if (map->ship_map[i][0] != '1' || map->ship_map[i]
			[map->width - 1] != '1')
			return (ft_printf(
					"Error: Map must be enclosed by walls (1) at sides\n"), 0);
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
		return (0);
	if (!count_elements(map, &p_count, &e_count, &c_count))
		return (0);
	if (map_errors(p_count, c_count, e_count))
		return (0);
	if (!check_walls(map))
		return (0);
	if (!check_valid_path(map))
		return (0);
	return (1);
}

int	allocate_map_memory(t_map **map, char ***temp_map, int fd)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_printf("Error: Failed to allocate memory for map\n"),
			close(fd), EXIT_FAILURE);
	*temp_map = ft_calloc(200 + 1, sizeof(char *));
	if (!*temp_map)
		return (ft_printf("Error: Failed to allocate memory for map\n"),
			close(fd), free(*map), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	read_map_lines(int fd, char **temp_map)
{
	char	*line;
	size_t	lines_read;

	lines_read = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (lines_read >= 200)
			return (ft_printf("Error: Map too large\n"), free(line),
				ft_free_matrix((void **)temp_map), EXIT_FAILURE);
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		temp_map[lines_read++] = line;
		line = get_next_line(fd);
	}
	if (lines_read == 0)
		return (ft_printf("Error: Map file is empty\n"),
			ft_free_matrix((void **)temp_map), EXIT_FAILURE);
	return ((int)lines_read);
}

size_t	parse_map(t_game *game, char *map_path)
{
	int		fd;
	t_map	*map;
	char	**temp_map;
	size_t	lines_read;

	if (!has_ber_extension(map_path))
		return (ft_printf("Error: Invalid file extension. Expected .ber\n"),
			EXIT_FAILURE);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error: Failed to open map file\n"), EXIT_FAILURE);
	if (allocate_map_memory(&map, &temp_map, fd) == 1)
		return (close(fd), EXIT_FAILURE);
	lines_read = read_map_lines(fd, temp_map);
	if (lines_read == 1)
		return (ft_free((void **)&map), close(fd), EXIT_FAILURE);
	map->ship_map = temp_map;
	map->height = lines_read;
	map->width = ft_strlen(temp_map[0]);
	if (!validate_map(map))
		return (ft_free_matrix((void **)map->ship_map), free(map), close(fd),
			EXIT_FAILURE);
	game->map = map;
	return (close(fd), EXIT_SUCCESS);
}
