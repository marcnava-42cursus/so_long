/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:00:44 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 07:07:03 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	handle_rotation(t_game *game, char cmd)
{
	size_t	y;
	size_t	x;
	char	new_facing;

	x = game->player.ship_x;
	y = game->player.ship_y;
	if (cmd == 'l')
		new_facing = rotate_facing_left(game->player.facing);
	else
		new_facing = rotate_facing_right(game->player.facing);
	game->player.facing = new_facing;
	game->map->ship_map[y][x] = get_ship_tile(new_facing);
	draw_cell(game, y, x);
}

static void	execute_command(t_game *game, char cmd)
{
	if (cmd == 'u')
		move_ship_forward(game);
	else if (cmd == 'l' || cmd == 'r')
		handle_rotation(game, cmd);
	else if (cmd == 'b')
		game->instruction_index = 0;
}

void	step_instruction(void *param)
{
	t_game	*game;
	float	dt;
	size_t	len;
	char	cmd;

	game = (t_game *)param;
	if (!game->running)
		return ;
	dt = game->mlx->delta_time;
	game->instruction_timer += dt;
	len = ft_strlen(game->instructions);
	while (game->instruction_timer >= game->speed)
	{
		game->instruction_timer -= game->speed;
		if (game->instruction_index >= (int)len)
		{
			game->running = 0;
			ft_printf("All instructions executed\n");
			break ;
		}
		cmd = game->instructions[game->instruction_index++];
		ft_printf("Instruction: %c\n", cmd);
		execute_command(game, cmd);
	}
}

static void	key_pressed_handler(mlx_key_data_t kd, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (kd.action != MLX_PRESS)
		return ;
	if (kd.key == MLX_KEY_ESCAPE || kd.key == MLX_KEY_Q)
		cleanup_and_exit(game);
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
	render_moves(game);
	render_instructions(game);
}

void	handle_key(mlx_key_data_t kd, void *param)
{
	debug_instructions(kd, param);
	key_pressed_handler(kd, param);
}
