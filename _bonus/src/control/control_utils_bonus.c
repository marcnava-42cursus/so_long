/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:09:41 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 21:27:36 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	can_ship_move(t_game *game, int x, int y)
{
	int	width;
	int	height;

	width = (int) game->map->width;
	height = (int) game->map->height;
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		ft_printf("You cannot move outside the map boundaries\n");
		return (0);
	}
	return (1);
}

int	in_bounds(t_game *game, int x, int y)
{
	int	width;

	width = (int) game->map->width;
	if (x < 0)
		return (0);
	if (y < 0)
		return (0);
	if (x >= width)
		return (0);
	if (y > 6)
		return (0);
	return (1);
}

void	clear_cell(t_game *game, int x, int y)
{
	if (game->map->baba_image_map[y][x] == NULL)
		return ;
	mlx_delete_image(game->mlx, game->map->baba_image_map[y][x]);
	game->map->baba_image_map[y][x] = NULL;
}

void	draw_tile(t_game *game, int x, int y, char tile)
{
	game->map->baba_map[y][x] = tile;
	clear_cell(game, x, y);
	draw_baba_cell(game, x, y, tile);
}

int	is_generator(char tile)
{
	if (tile >= '4' && tile <= '7')
		return (1);
	return (0);
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
