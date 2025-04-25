/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:58:48 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 04:57:19 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_min_width(t_map *map)
{
	size_t	i;
	size_t	j;
	size_t	old_width;

	if (map->width >= 7)
		return (1);
	old_width = map->width;
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
	map->width = 7;
	return (1);
}


static int	validate_map(t_map *map)
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
		return (ft_printf("Error: No solvable map\n"), 0);
	if (!check_min_width(map))
		return (ft_printf("Error: Cannot add extra chars to map\n"), 0);
	return (1);
}

static int	allocate_map_memory(t_map **map, char ***temp_map, int fd)
{
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (ft_printf("Error: Failed to allocate memory for map\n"),
			close(fd), EXIT_FAILURE);
	*temp_map = ft_calloc(1024, sizeof(char *));
	if (!*temp_map)
		return (ft_printf("Error: Failed to allocate memory for map\n"),
			close(fd), free(*map), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	allocate_baba_map_memory(t_map *map)
{
	size_t	y;

	map->baba_map = ft_calloc(7 + 1, sizeof(char *));
	if (!map->baba_map)
	{
		ft_printf("Error: Malloc baba_map failed\n");
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < 7)
	{
		map->baba_map[y] = ft_calloc(map->width + 1, sizeof(char));
		if (!map->baba_map[y])
		{
			ft_printf("Error: Malloc baba_map row failed\n");
			exit(EXIT_FAILURE);
		}
		map->baba_map[y][map->width] = '\0';
		y++;
	}
	map->baba_map[7] = NULL;
}

static int	read_map_lines(int fd, char **temp_map)
{
	char	*line;
	size_t	lines_read;

	lines_read = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			ft_free((void **)&line);
			line = get_next_line(fd);
			continue ;
		}
		if (lines_read >= 1024)
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

	ft_printf("Parsing map: %s\n", map_path);
	if (!has_ber_extension(map_path))
		return (ft_printf("Error: Invalid file extension. Expected .ber\n"),
			EXIT_FAILURE);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error: Failed to open map file\n"), EXIT_FAILURE);

	if (allocate_map_memory(&map, &temp_map, fd) == 1)
		return (ft_printf("Error: Failed to allocate memory\n"), EXIT_FAILURE);

	lines_read = read_map_lines(fd, temp_map);
	if (lines_read == 1)
	{
		free(map);
		close(fd);
		return (EXIT_FAILURE);
	}

	map->ship_map = temp_map;
	map->height = lines_read;
	map->width = ft_strlen(temp_map[0]);

	allocate_baba_map_memory(map);

	if (!validate_map(map))
	{
		ft_free_matrix((void **)map->ship_map);
		free(map);
		close(fd);
		return (EXIT_FAILURE);
	}

	game->map = map;
	close(fd);
	return (EXIT_SUCCESS);
}
