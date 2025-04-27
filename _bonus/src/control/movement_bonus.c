/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:02:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 21:17:30 by marcnava         ###   ########.fr       */
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

static void	handle_push_tile(t_game *game, char tile,
	int ny, int nx, int dx, int dy)
{
	if (is_pushable(tile))
		push_block(game, ny, nx, dx, dy);
}

static void	restore_previous(t_game *game, int ox, int oy)
{
	char	prev;
	char	restore;

	prev = game->prev_baba_tile;
	/* por defecto restauramos suelo '8' */
	restore = '8';
	/* si prev era un tile válido distinto de '0', lo restauramos */
	if (prev == '2'
	 || prev == '3'
	 || prev == 'a'
	 || (prev >= '4' && prev <= '7'))
	{
		restore = prev;
	}
	draw_tile(game, ox, oy, restore);
}

static void	maybe_generate(t_game *game, char tile, int ny, int nx)
{
	if (is_generator(tile))
		generate_block(game, ny, nx, tile);
}

static void	update_prev_and_draw(t_game *game, char tile, int nx, int ny)
{
	if (is_pushable(tile))
		game->prev_baba_tile = '8';
	else
		game->prev_baba_tile = tile;
	draw_tile(game, nx, ny, 'p');
	game->player.baba_x = nx;
	game->player.baba_y = ny;
}

int	move_baba(t_game *game, int dx, int dy)
{
	char	tile;
	int		ox;
	int		oy;
	int		nx;
	int		ny;
	int		success;

	ox = game->player.baba_x;
	oy = game->player.baba_y;
	nx = ox + dx;
	ny = oy + dy;
	if (can_move(game, nx, ny) == 0)
		return (0);
	tile = game->map->baba_map[ny][nx];
	success = handle_wall(tile);
	if (success == 0)
		return (1);
	handle_delete_button(game, tile);
	handle_push_tile(game, tile, ny, nx, dx, dy);
	restore_previous(game, ox, oy);
	maybe_generate(game, tile, ny, nx);
	update_prev_and_draw(game, tile, nx, ny);
	if (tile == 'a')
		execute_instructions(game);
	return (1);
}
