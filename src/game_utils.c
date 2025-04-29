/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 02:28:32 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	init_game(t_game *game, char *map_path)
{
	int	screen_w;
	int	screen_h;
	int	req_w;
	int	req_h;

	if (parse_map(game, map_path) == 1)
		exit(EXIT_FAILURE);
	req_w = game->map->width * TILE_SIZE;
	req_h = game->map->height * TILE_SIZE;
	game->mlx = mlx_init(req_w, req_h, TITLE, false);
	if (!game->mlx)
	{
		ft_printf("Error: Failed to initialize mlx\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}
	mlx_get_monitor_size(0, &screen_w, &screen_h);
	if (req_w > screen_w || req_h > screen_h)
	{
		ft_printf("Map bigger than current window\n");
		cleanup_and_exit(game);
		exit(EXIT_FAILURE);
	}
	return (load_textures(game), game->moves = 0, draw_map(game), EXIT_SUCCESS);
}
