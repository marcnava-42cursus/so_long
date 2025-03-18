/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/07 20:15:45 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int32_t	init_game(t_game *game, char *map_path)
{
	game->mlx = mlx_init(800, 600, TITLE, false);
	if (!game->mlx)
	{
		ft_printf("Error\nFailed to initialize mlx\n");
		return (EXIT_FAILURE);
	}
	if (parse_map(game, map_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int32_t	parse_map(t_game *game, char *map_path)
{
	int32_t	fd;
	char	*line;
	t_map	*map;

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		return (ft_printf("Error\nFailed to open map file\n"), EXIT_FAILURE);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (ft_printf("Error\nFailed to allocate memory for map\n"),
			EXIT_FAILURE);
	map->map = ft_lstnew(NULL);
	if (!map->map)
		return (ft_printf("Error\nFailed to allocate memory for map\n"),
			EXIT_FAILURE);
	while ((line = get_next_line(fd)) > 0)
	{
		ft_lstadd_back(&map->map, ft_lstnew(line));
		map->height++;
	}
	map->width = ft_strlen(*map->map);
	game->map = map;
	return (EXIT_SUCCESS);
}

void	free_map(t_map *map)
{
	while (*(map->map))
	{
		free(*(map->map));
		(map->map)++;
	}
	free(map);
}

void	free_game(t_game *game)
{
	free_map(game->map);
	mlx_destroy(game->mlx);
	free(game);
}
