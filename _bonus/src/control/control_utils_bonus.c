/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:41:40 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 09:53:55 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

//! DEPRECATED
int	can_ship_move(t_game *game, int x, int y)
{
	int	width;
	int	height;

	width = (int) game->map->width;
	height = (int) game->map->height;
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		ft_printf("You cannot move outside the map boundaries\n");
		return (0);
	}
	return (1);
}

int	in_bounds(t_game *game, int x, int y)
{
	int	width;

	width = (int) game->map->width;
	if (x < 0)
		return (0);
	if (y < 0)
		return (0);
	if (x >= width)
		return (0);
	if (y > 6)
		return (0);
	return (1);
}

void	clear_cell(t_game *game, int x, int y)
{
	if (game->map->baba_image_map[y][x] == NULL)
		return ;
	mlx_delete_image(game->mlx, game->map->baba_image_map[y][x]);
	game->map->baba_image_map[y][x] = NULL;
}

void	draw_tile(t_game *game, int x, int y, char tile)
{
	game->map->baba_map[y][x] = tile;
	clear_cell(game, x, y);
	draw_baba_cell(game, x, y, tile);
}
