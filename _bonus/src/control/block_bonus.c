/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:04:10 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 21:15:33 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	push_block(t_game *game, int dx, int dy)
{
	int		bx;
	int		by;
	char	tile;
	char	dest;

	bx = (game->player.baba_x + dx) + dx;
	by = (game->player.baba_y + dy) + dy;
	if (in_bounds(game, bx, by) == 0)
		return (0);
	tile = game->map->baba_map[(game->player.baba_y + dy)]
	[(game->player.baba_x + dx)];
	dest = game->map->baba_map[by][bx];
	if (dest == '8')
		draw_tile(game, bx, by, tile);
	else
	{
		if (dest == '2')
			add_instruction(game, tile);
	}
	draw_tile(game, (game->player.baba_x + dx),
		(game->player.baba_y + dy), '8');
	return (1);
}
