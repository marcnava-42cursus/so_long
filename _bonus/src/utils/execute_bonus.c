/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:05:23 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/27 17:21:53 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	check_coins(t_game *game)
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

static int	check_boundaries(t_game *game, int x, int y)
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

static int	handle_destination(t_game *game, int new_x, int new_y)
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
	return (1);
}

static void	perform_move(t_game *game, int cur_x, int cur_y,
		int new_x, int new_y)
{
	game->map->ship_map[cur_y][cur_x] = '0';
	draw_cell(game, cur_y, cur_x);
	game->map->ship_map[new_y][new_x] = 'P';
	game->player.ship_x = (size_t) new_x;
	game->player.ship_y = (size_t) new_y;
	draw_cell(game, new_y, new_x);
}

static int	finalize_move(t_game *game)
{
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	return (1);
}

int	move_ship(t_game *game, int dx, int dy)
{
	int	cur_x;
	int	cur_y;
	int	new_x;
	int	new_y;

	cur_x = (int) game->player.ship_x;
	cur_y = (int) game->player.ship_y;
	new_x = cur_x + dx;
	new_y = cur_y + dy;
	if (check_boundaries(game, new_x, new_y) == 0)
		return (0);
	if (handle_destination(game, new_x, new_y) == 0)
		return (0);
	perform_move(game, cur_x, cur_y, new_x, new_y);
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
