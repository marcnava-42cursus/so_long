/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:15:02 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/27 18:39:16 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".ber", 4));
}

static int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'P' || c == 'C' || c == 'E');
}

static int	validate_map(t_map *map)
{
	size_t	i, j;
	int		p_count, e_count, c_count;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = 0;
	while (i < map->height)
	{
		if (ft_strlen(map->map[i]) != map->width)
			return (ft_printf("Error\nMap rows must have the same width\n"), 0);
		
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_char(map->map[i][j]))
				return (ft_printf("Error\nInvalid character in map: %c\n", map->map[i][j]), 0);
			if (map->map[i][j] == 'P') p_count++;
			if (map->map[i][j] == 'E') e_count++;
			if (map->map[i][j] == 'C') c_count++;
			j++;
		}
		i++;
	}
	if (p_count != 1)
		return (ft_printf("Error\nMap must have exactly 1 player (P), found %d\n", p_count), 0);
	if (e_count != 1)
		return (ft_printf("Error\nMap must have exactly 1 exit (E), found %d\n", e_count), 0);
	if (c_count < 1)
		return (ft_printf("Error\nMap must have at least 1 collectible (C)\n"), 0);
	j = 0;
	while (j < map->width)
	{
		if (map->map[0][j] != '1' || map->map[map->height - 1][j] != '1')
			return (ft_printf("Error\nMap must be enclosed by walls (1) at top and bottom\n"), 0);
		j++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
			return (ft_printf("Error\nMap must be enclosed by walls (1) at sides\n"), 0);
		i++;
	}
	if (!check_valid_path(map))
		return (0);
	return (1);
}

size_t	parse_map(t_game *game, char *map_path)
{
	int		fd;
	char	*line;
	t_map	*map;
	char	**temp_map;
	size_t	lines_read = 0;

	if (!has_ber_extension(map_path))
		return (ft_printf("Error\nInvalid file extension. Expected .ber\n"), EXIT_FAILURE);
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFailed to open map file\n"), EXIT_FAILURE);

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (ft_printf("Error\nFailed to allocate memory for map\n"), close(fd), EXIT_FAILURE);
	temp_map = ft_calloc(1024, sizeof(char *));
	if (!temp_map)
	{
		free(map);
		close(fd);
		return (ft_printf("Error\nFailed to allocate memory for map\n"), EXIT_FAILURE);
	}

	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n') // Evitar líneas vacías
		{
			free(line);
			continue ;
		}
		if (lines_read >= 1024) // Evitar desbordamiento
		{
			free(line);
			ft_free_matrix((void **)temp_map);
			free(map);
			close(fd);
			return (ft_printf("Error\nMap too large\n"), EXIT_FAILURE);
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		temp_map[lines_read++] = line;
	}

	if (lines_read == 0)
	{
		ft_free_matrix((void **)temp_map);
		free(map);
		close(fd);
		return (ft_printf("Error\nMap file is empty\n"), EXIT_FAILURE);
	}

	map->map = temp_map;
	map->height = lines_read;
	map->width = ft_strlen(temp_map[0]);

	if (!validate_map(map))
	{
		ft_free_matrix((void **)map->map);
		free(map);
		close(fd);
		return (EXIT_FAILURE);
	}

	game->map = map;
	close(fd);
	return (EXIT_SUCCESS);
}
