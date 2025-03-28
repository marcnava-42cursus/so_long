/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/28 22:41:08 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	init_game(t_game *game, char *map_path)
{	
	if (parse_map(game, map_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
		game->map->height * TILE_SIZE,
		TITLE, false);
	if (!game->mlx)
		return (ft_printf("Error\nFailed to initialize mlx\n"), EXIT_FAILURE);

	load_textures(game);
	draw_map(game);

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
	mlx_terminate(game->mlx);
	free(game);
}
