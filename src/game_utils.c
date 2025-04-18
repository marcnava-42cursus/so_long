/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:37:45 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	init_game(t_game *game, char *map_path)
{
	if (parse_map(game, map_path) == 1)
		exit(EXIT_FAILURE);
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE,
			TITLE, false);
	if (!game->mlx)
		return (ft_printf("Error\nFailed to initialize mlx\n"), EXIT_FAILURE);
	load_textures(game);
	game->moves = 0;
	draw_map(game);
	return (EXIT_SUCCESS);
}
