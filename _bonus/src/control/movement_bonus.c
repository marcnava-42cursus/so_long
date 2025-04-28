/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:02:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 06:59:41 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	can_move(t_game *game, int nx, int ny)
{
	if (in_bounds(game, nx, ny) == 1)
		return (1);
	ft_printf("You cannot move outside the map boundaries\n");
	return (0);
}

static int	handle_wall(char tile)
{
	if (tile == '9')
	{
		ft_printf("You cannot walk through a wall\n");
		return (0);
	}
	return (1);
}

static void	handle_delete_button(t_game *game, char tile)
{
	if (tile == '3')
		remove_instruction(game);
}

static void	handle_push_tile(t_game *game, char tile, int dx, int dy)
{
	if (is_pushable(tile))
		push_block(game, dx, dy);
}

static void	restore_previous(t_game *game, int ox, int oy)
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

static void	maybe_generate(t_game *game, char tile, int nx, int ny)
{
	if (is_generator(tile))
		generate_block(game, nx, ny, tile);
}

static char	determine_sprite(int dx, int dy)
{
	if (dx == 1 && dy == 0)
		return (BABA_EAST);
	if (dx == -1 && dy == 0)
		return (BABA_WEST);
	if (dx == 0 && dy == 1)
		return (BABA_SOUTH);
	return (BABA_NORTH);
}

static void	apply_tile_effects(t_game *game, char tile, int dx, int dy)
{
	handle_delete_button(game, tile);
	handle_push_tile(game, tile, dx, dy);
	restore_previous(game, game->player.baba_x, game->player.baba_y);
	maybe_generate(game, tile, game->player.baba_x + dx,
		game->player.baba_y + dy);
}

static void	update_prev_tile(t_game *game, char tile)
{
	if (is_pushable(tile))
		game->prev_baba_tile = '8';
	else
		game->prev_baba_tile = tile;
}

static void	finalize_move(t_game *game, int nx, int ny, char sprite)
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
	finalize_move(game, nx, ny, sprite);
	if (tile == 'a')
		execute_instructions(game);
	return (1);
}
