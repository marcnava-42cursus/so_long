/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship_checks_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:07:46 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:29:47 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	check_coins(t_game *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			if (game->map->ship_map[row][col] == 'C')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	check_boundaries(t_game *game, int x, int y)
{
	int	width;
	int	height;

	width = (int) game->map->width;
	height = (int) game->map->height;
	if (x < 0 || x >= width || y < 0 || y >= height)
	{
		ft_printf("You cannot move outside the map boundaries\n");
		return (0);
	}
	return (1);
}

int	handle_destination(t_game *game, int new_x, int new_y)
{
	char	dest;

	dest = game->map->ship_map[new_y][new_x];
	if (dest == '1')
		return (0);
	if (dest == 'E')
	{
		if (check_coins(game))
			return (0);
		mlx_close_window(game->mlx);
	}
	if (dest == 'M')
		mlx_close_window(game->mlx);
	return (1);
}

void	perform_move(t_game *game, int new_x, int new_y)
{
	int		cur_x;
	int		cur_y;
	char	tile;

	cur_x = (int)game->player.ship_x;
	cur_y = (int)game->player.ship_y;
	tile = get_ship_tile(game->player.facing);
	game->map->ship_map[cur_y][cur_x] = '0';
	draw_cell(game, cur_y, cur_x);
	game->map->ship_map[new_y][new_x] = tile;
	game->player.ship_x = new_x;
	game->player.ship_y = new_y;
	draw_cell(game, new_y, new_x);
}

int	finalize_move(t_game *game)
{
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	return (1);
}
