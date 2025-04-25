/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:08:27 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 21:08:48 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	generate_block(t_game *game, int y, int x, char gen_tile)
{
	int door_x;

	door_x = x + 1;
	if (in_bounds(game, door_x, y) == 0)
		return;

	draw_tile(
		game,
		door_x,
		y,
		door_for(gen_tile)
	);
}
