/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:18:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 18:40:53 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	mlx_image_t	*get_image_for_tile(char tile, t_game *game)
{
	if (tile == '1')
		return (game->textures->wall);
	else if (tile == 'P')
		return (game->textures->player);
	else if (tile == 'E')
		return (game->textures->exit);
	else if (tile == 'C')
		return (game->textures->collect);
	else
		return (game->textures->floor);
}

static void	update_player_position(char tile, size_t row, size_t col,
	t_game *game)
{
	if (tile == 'P')
	{
		game->player.ship_x = col;
		game->player.ship_y = row;
	}
}

void	draw_map(t_game *game)
{
	size_t		row;
	size_t		col;
	mlx_image_t	*img;
	char		tile;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			tile = game->map->ship_map[row][col];
			update_player_position(tile, row, col, game);
			img = get_image_for_tile(tile, game);
			mlx_image_to_window(game->mlx, img, col * TILE_SIZE,
				row * TILE_SIZE);
			col++;
		}
		row++;
	}
}

void	draw_tile(t_game *game, size_t row, size_t col)
{
	mlx_image_t	*img;
	char		tile;

	tile = game->map->ship_map[row][col];
	img = get_image_for_tile(tile, game);
	mlx_image_to_window(game->mlx, img, col * TILE_SIZE, row * TILE_SIZE);
}
