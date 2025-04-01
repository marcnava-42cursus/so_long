/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/01 16:29:51 by marcnava         ###   ########.fr       */
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
	game->moves = 0;
	draw_map(game);
	return (EXIT_SUCCESS);
}
