/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:00:44 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/24 20:03:38 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"


static int move_baba(t_game *game, int dx, int dy)
{
	int old_x;
	int old_y;

	old_x = game->player.baba_x;
	old_y = game->player.baba_y;
	if ((old_x + dx) < 0 || (old_y + dy) < 0
		|| (old_x + dx) > (int)game->map->width || (old_y + dy) > 6)
		return (ft_printf("You are in the border, cannot move\n"), 0);
	if (game->map->baba_map[old_y + dy][old_x + dx] == '9')
		return (ft_printf("You cannot walk throught a wall\n"), 0);
	if (game->prev_baba_tile == '0')
		game->prev_baba_tile = '8';
	game->map->baba_map[old_y][old_x] = game->prev_baba_tile;
	game->prev_baba_tile = game->map->baba_map[old_y + dy][old_x + dx];
	game->map->baba_map[old_y + dy][old_x + dx] = 'p';
	if (game->map->baba_image_map[old_y][old_x])
		mlx_delete_image(game->mlx, game->map->baba_image_map[old_y][old_x]);
	draw_baba_cell(game, old_x, old_y, game->map->baba_map[old_y][old_x]);
	game->player.baba_x = old_x + dx;
	game->player.baba_y = old_y + dy;
	if (game->map->baba_image_map[old_y + dy][old_x + dx])
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[old_y + dy][old_x + dx]);
	return (draw_baba_cell(game, old_x + dx, old_y + dy,
		game->map->baba_map[old_y + dy][old_x + dx]), 1);
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
		|| keydata.key == MLX_KEY_K || keydata.key == KEY_NUMPAD_8)
		move_baba(game, 0, -1);
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT
		|| keydata.key == MLX_KEY_H || keydata.key == KEY_NUMPAD_4)
		move_baba(game, -1, 0);
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_J || keydata.key == KEY_NUMPAD_2)
		move_baba(game, 0, 1);
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT
		|| keydata.key == MLX_KEY_L || keydata.key == KEY_NUMPAD_6)
		move_baba(game, 1, 0);
}
