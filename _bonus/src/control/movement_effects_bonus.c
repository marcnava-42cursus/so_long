/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_effects_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:02:21 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:22:53 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	apply_tile_effects(t_game *game, char tile, int dx, int dy)
{
	handle_delete_button(game, tile);
	handle_push_tile(game, tile, dx, dy);
	restore_previous(game, game->player.baba_x, game->player.baba_y);
	maybe_generate(game, tile, game->player.baba_x + dx,
		game->player.baba_y + dy);
}

char	determine_sprite(int dx, int dy)
{
	if (dx == 1 && dy == 0)
		return (BABA_EAST);
	if (dx == -1 && dy == 0)
		return (BABA_WEST);
	if (dx == 0 && dy == 1)
		return (BABA_SOUTH);
	return (BABA_NORTH);
}

void	finalize_baba_move(t_game *game, int nx, int ny, char sprite)
{
	draw_tile(game, nx, ny, sprite);
	game->player.baba_x = nx;
	game->player.baba_y = ny;
}

int	move_baba(t_game *game, int dx, int dy)
{
	int		nx;
	int		ny;
	char	tile;
	char	sprite;

	nx = game->player.baba_x + dx;
	ny = game->player.baba_y + dy;
	if (!can_move(game, nx, ny))
		return (0);
	tile = game->map->baba_map[ny][nx];
	if (!handle_wall(tile))
		return (1);
	sprite = determine_sprite(dx, dy);
	apply_tile_effects(game, tile, dx, dy);
	update_prev_tile(game, tile);
	finalize_baba_move(game, nx, ny, sprite);
	if (tile == 'a')
		execute_instructions(game);
	return (1);
}
