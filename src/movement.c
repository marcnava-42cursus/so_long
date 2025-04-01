/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 22:20:53 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/01 16:38:40 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			if (game->map->map[row][col] == 'C')
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

static int	move_player(t_game *game, size_t dx, size_t dy)
{
	size_t	new_x;
	size_t	new_y;
	char	prev;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (game->map->map[new_y][new_x] == '1')
		return (0);
	if (game->map->map[new_y][new_x] == 'E')
	{
		if (check_coins(game))
			return (0);
		mlx_close_window(game->mlx);
	}
	prev = game->map->map[new_y][new_x];
	if (prev == 'C')
		game->map->map[new_y][new_x] = '0';
	game->map->map[game->player.y][game->player.x] = '0';
	draw_tile(game, game->player.y, game->player.x);
	game->map->map[new_y][new_x] = 'P';
	game->player.x = new_x;
	game->player.y = new_y;
	draw_tile(game, new_y, new_x);
	return (1);
}

void	key_pressed_handler(mlx_key_data_t keydata, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE || keydata.key == MLX_KEY_Q)
	{
		cleanup_and_exit(game);
		exit(EXIT_SUCCESS);	
	}
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP
		|| keydata.key == MLX_KEY_K)
		move_player(game, 0, -1);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT
		|| keydata.key == MLX_KEY_H)
		move_player(game, -1, 0);
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_J)
		move_player(game, 0, 1);
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT
		|| keydata.key == MLX_KEY_L)
		move_player(game, 1, 0);
	ft_printf("Moves: %d\n", ++game->moves);
}

void	close_window_handler(void *param)
{
	cleanup_and_exit((t_game *)param);
	exit(EXIT_SUCCESS);
}
