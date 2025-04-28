/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_checks_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 07:57:21 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:26:03 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	can_move(t_game *game, int nx, int ny)
{
	if (in_bounds(game, nx, ny) == 1)
		return (1);
	ft_printf("You cannot move outside the map boundaries\n");
	return (0);
}

int	handle_wall(char tile)
{
	if (tile == '9')
	{
		ft_printf("You cannot walk through a wall\n");
		return (0);
	}
	return (1);
}

int	is_pushable(char tile)
{
	if (tile == 'l')
		return (1);
	if (tile == 'r')
		return (1);
	if (tile == 'u')
		return (1);
	if (tile == 'b')
		return (1);
	return (0);
}

int	is_generator(char tile)
{
	if (tile >= '4' && tile <= '7')
		return (1);
	return (0);
}

char	door_for(char tile)
{
	if (tile == '4')
		return ('l');
	if (tile == '5')
		return ('r');
	if (tile == '6')
		return ('u');
	return ('b');
}
