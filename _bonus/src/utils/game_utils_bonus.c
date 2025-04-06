/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:44:29 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:46:49 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

size_t	init_game(t_game *game, char *map_path)
{
	if (parse_map(game, map_path) == 1)
		exit(EXIT_FAILURE);
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE,
			TITLE, false);
	if (!game->mlx)
		return (ft_printf("Error: Failed to initialize mlx\n"), EXIT_FAILURE);
	game->moves = 0;
	game->textures = NULL;
	render_map(game);
	return (EXIT_SUCCESS);
}
