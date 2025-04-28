/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship_actions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:16:12 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:28:26 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	move_ship(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = (int)game->player.ship_x + dx;
	new_y = (int)game->player.ship_y + dy;
	if (check_boundaries(game, new_x, new_y) == 0)
		return (0);
	if (handle_destination(game, new_x, new_y) == 0)
		return (0);
	perform_move(game, new_x, new_y);
	return (finalize_move(game));
}

void	move_ship_forward(t_game *game)
{
	ft_printf("Facing: %c\n", game->player.facing);
	if (game->player.facing == 'n')
		move_ship(game, 0, -1);
	else if (game->player.facing == 'w')
		move_ship(game, -1, 0);
	else if (game->player.facing == 'e')
		move_ship(game, 1, 0);
	else if (game->player.facing == 's')
		move_ship(game, 0, 1);
}

void	execute_instructions(t_game *game)
{
	size_t	len;

	len = ft_strlen(game->instructions);
	if (len == 0)
	{
		ft_printf("No instructions given\n");
		return ;
	}
	game->running = 1;
	game->instruction_index = 0;
	game->instruction_timer = 0.0f;
}

char	get_ship_tile(char facing)
{
	if (facing == 'n')
		return (SHIP_NORTH);
	if (facing == 's')
		return (SHIP_SOUTH);
	if (facing == 'w')
		return (SHIP_WEST);
	if (facing == 'e')
		return (SHIP_EAST);
	return (SHIP_NORTH);
}
