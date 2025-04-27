/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:00:44 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/27 17:22:48 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	step_instruction(void *param)
{
	t_game	*game;
	float	dt;
	char	cmd;

	game = (t_game *)param;
	dt = game->mlx->delta_time;
	if (!game->running)
		return ;
	game->instruction_timer += dt;
	while (game->instruction_timer >= game->speed)
	{
		game->instruction_timer -= game->speed;
		if (game->instruction_index >= (int)ft_strlen(game->instructions))
		{
			game->running = 0;
			ft_printf("All instructions executed\n");
		}
		cmd = game->instructions[game->instruction_index++];
		ft_printf("Instruction: %c\n", cmd);
		if (cmd == 'u')
			move_ship_forward(game);
		else if (cmd == 'l')
			game->player.facing = rotate_facing_left(game->player.facing);
		else if (cmd == 'r')
			game->player.facing = rotate_facing_right(game->player.facing);
		else if (cmd == 'b')
			game->instruction_index = 0;
	}
}

static void	key_pressed_handler(mlx_key_data_t kd, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (kd.action != MLX_PRESS)
		return ;
	if (kd.key == MLX_KEY_ESCAPE || kd.key == MLX_KEY_Q)
	{
		cleanup_and_exit(game);
		exit(EXIT_SUCCESS);
	}
	if (game->running == 0)
	{
		if (kd.key == MLX_KEY_W || kd.key == MLX_KEY_UP
			|| kd.key == MLX_KEY_K || kd.key == KEY_NUMPAD_8)
			move_baba(game, 0, -1);
		if (kd.key == MLX_KEY_A || kd.key == MLX_KEY_LEFT
			|| kd.key == MLX_KEY_H || kd.key == KEY_NUMPAD_4)
			move_baba(game, -1, 0);
		if (kd.key == MLX_KEY_S || kd.key == MLX_KEY_DOWN
			|| kd.key == MLX_KEY_J || kd.key == KEY_NUMPAD_2)
			move_baba(game, 0, 1);
		if (kd.key == MLX_KEY_D || kd.key == MLX_KEY_RIGHT
			|| kd.key == MLX_KEY_L || kd.key == KEY_NUMPAD_6)
			move_baba(game, 1, 0);
	}
}

void	handle_key(mlx_key_data_t kd, void *param)
{
	debug_instructions(kd, param);
	key_pressed_handler(kd, param);
}
