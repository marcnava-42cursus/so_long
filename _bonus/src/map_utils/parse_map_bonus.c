/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:58:48 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 07:32:36 by marcnava         ###   ########.fr       */
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

static void	allocate_baba_map_memory(t_map *map)
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

static int	allocate_map_memory(t_map **map, char ***temp_map,
				size_t max_lines)
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

static char	*read_next_non_empty_line(int fd)
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

static size_t	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	return (len);
}

static int	add_row(char **temp_map, char *line, size_t idx)
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

static int	read_map_lines(int fd, char **temp_map)
{
	char	*line;
	size_t	lines_read;
	int		status;

	lines_read = 0;
	line = read_next_non_empty_line(fd);
	while (line)
	{
		status = add_row(temp_map, line, lines_read);
		if (status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		lines_read++;
		line = read_next_non_empty_line(fd);
	}
	if (lines_read == 0)
	{
		ft_printf("Error: Map file is empty\n");
		return (EXIT_FAILURE);
	}
	return ((int)lines_read);
}

static void	print_parsing_message(char *map_path)
{
	ft_printf("Parsing map: %s\n", map_path);
}

static int	validate_extension(char *map_path)
{
	if (!has_ber_extension(map_path))
	{
		ft_printf("Error: Invalid file extension. Expected .ber\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	open_map_file(char *map_path, int *fd)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd == -1)
	{
		ft_printf("Error: Failed to open map file\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	load_temp_map(char *map_path, t_map **map,
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

static int	finalize_map(t_game *game, t_map *map,
			char **temp_map, size_t lines_read)
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

size_t	parse_map(t_game *game, char *map_path)
{
	t_map		*map;
	char		**temp_map;
	size_t		lines_read;
	int			status;

	print_parsing_message(map_path);
	status = validate_extension(map_path);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = load_temp_map(map_path, &map, &temp_map, &lines_read);
	if (status == EXIT_FAILURE || lines_read <= 1)
		return (EXIT_FAILURE);
	status = finalize_map(game, map, temp_map, lines_read);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
