/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:05:39 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 21:09:10 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void handle_floor_move(
	t_game *game,
	int by,
	int bx,
	char tile
)
{
	draw_tile(game, bx, by, tile);
}

static void handle_block_destroy(
	t_game *game,
	char dest,
	char tile
)
{
	if (dest == '2')
		add_instruction(game, tile);
}

int	push_block(t_game *game, int y, int x, int dx, int dy)
{
	int bx;
	int by;
	char tile;
	char dest;

	bx = x + dx;
	by = y + dy;
	if (in_bounds(game, bx, by) == 0)
		return 0;

	tile = game->map->baba_map[y][x];
	dest = game->map->baba_map[by][bx];

	if (dest == '8')
		handle_floor_move(game, by, bx, tile);
	else
		handle_block_destroy(game, dest, tile);

	draw_tile(game, x, y, '8');
	return 1;
}
