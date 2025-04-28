/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:00:05 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:24:45 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	handle_delete_button(t_game *game, char tile)
{
	if (tile == '3')
		remove_instruction(game);
}

void	handle_push_tile(t_game *game, char tile, int dx, int dy)
{
	if (is_pushable(tile))
		push_block(game, dx, dy);
}

void	maybe_generate(t_game *game, char tile, int nx, int ny)
{
	if (is_generator(tile))
		generate_block(game, nx, ny, tile);
}

void	restore_previous(t_game *game, int ox, int oy)
{
	char	prev;
	char	restore;

	prev = game->prev_baba_tile;
	restore = '8';
	if (prev == '2' || prev == '3' || prev == 'a'
		|| (prev >= '4' && prev <= '7'))
		restore = prev;
	draw_tile(game, ox, oy, restore);
}

void	update_prev_tile(t_game *game, char tile)
{
	if (is_pushable(tile))
		game->prev_baba_tile = '8';
	else
		game->prev_baba_tile = tile;
}
