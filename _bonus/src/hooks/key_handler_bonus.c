/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:00:44 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 21:05:04 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void key_pressed_handler(
	mlx_key_data_t kd,
	void *param
)
{
	t_game *game_ptr;

	game_ptr = (t_game *) param;
	if (kd.action != MLX_PRESS)
		return;

	if (kd.key == MLX_KEY_ESCAPE ||
		kd.key == MLX_KEY_Q)
	{
		cleanup_and_exit(game_ptr);
		exit(EXIT_SUCCESS);
	}

	if (kd.key == MLX_KEY_W ||
		kd.key == MLX_KEY_UP ||
		kd.key == MLX_KEY_K ||
		kd.key == KEY_NUMPAD_8)
	{
		move_baba(game_ptr, 0, -1);
	}
	if (kd.key == MLX_KEY_A ||
		kd.key == MLX_KEY_LEFT ||
		kd.key == MLX_KEY_H ||
		kd.key == KEY_NUMPAD_4)
	{
		move_baba(game_ptr, -1, 0);
	}
	if (kd.key == MLX_KEY_S ||
		kd.key == MLX_KEY_DOWN ||
		kd.key == MLX_KEY_J ||
		kd.key == KEY_NUMPAD_2)
	{
		move_baba(game_ptr, 0, 1);
	}
	if (kd.key == MLX_KEY_D ||
		kd.key == MLX_KEY_RIGHT ||
		kd.key == MLX_KEY_L ||
		kd.key == KEY_NUMPAD_6)
	{
		move_baba(game_ptr, 1, 0);
	}
}
