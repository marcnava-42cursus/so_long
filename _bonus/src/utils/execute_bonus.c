/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:05:23 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 01:52:10 by marcnava         ###   ########.fr       */
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

// execute_bonus.c

static int	move_ship(t_game *game, int dx, int dy)
{
	int		cur_x;
	int		cur_y;
	int		new_x;
	int		new_y;
	int		width;
	int		height;
	char	dest;

	/* 1) Coordenadas actuales */
	cur_x  = (int) game->player.ship_x;
	cur_y  = (int) game->player.ship_y;

	/* 2) Destino calculado */
	new_x  = cur_x + dx;
	new_y  = cur_y + dy;

	/* 3) Límites del mapa */
	width  = (int) game->map->width;
	height = (int) game->map->height;

	ft_printf("ox-oy : nx-ny -> (%d,%d) : (%d, %d)\n", game->player.ship_x, game->player.ship_y, new_x, new_y);
	
	if (new_x < 0 || new_x >= width ||
		new_y < 0 || new_y >= height)
	{
		ft_printf("You cannot move outside the map boundaries\n");
		return 0;
	}

	/* 4) Qué hay en destino */
	dest = game->map->ship_map[new_y][new_x];
	if (dest == '1')
		return 0;
	if (dest == 'E')
	{
		if (check_coins(game))
			return 0;
		mlx_close_window(game->mlx);
	}

	/* 5) Borra la vieja */
	game->map->ship_map[cur_y][cur_x] = '0';
	draw_cell(game, cur_y, cur_x);

	/* 6) Coloca la nueva */
	game->map->ship_map[new_y][new_x] = 'P';
	game->player.ship_x = (size_t) new_x;
	game->player.ship_y = (size_t) new_y;
	draw_cell(game, new_y, new_x);

	/* 7) Cuenta y muestra */
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);

	sleep(1);
	
	return 1;
}

static void move_ship_forward(t_game *game)
{
	switch (game->player.facing)
	{
		case 'n':
			move_ship(game, 0, -1);
			break;
		case 'w':
			move_ship(game, -1, 0);
			break;
		case 'e':
			move_ship(game, 1, 0);
			break;
		case 's':
			move_ship(game, 0, 1);
			break;
		default:
			break;
	}
}

static double  accumulator = 0.0;

static void step_instruction(void *param)
{
	t_game *game = (t_game *)param;

	if (game->running == 0)
		return;

	/* 1) Acumula delta time interno */
	accumulator += game->mlx->delta_time;
	if (accumulator < EXEC_SPEED)
		return;
	accumulator -= EXEC_SPEED;

	/* 2) ¿Quedan instrucciones? */
	size_t idx = game->instruction_index;
	size_t len = ft_strlen(game->instructions);
	if (idx >= len)
	{
		game->running = 0;
		return;
	}

	/* 3) Toma y ejecuta el comando */
	char cmd = game->instructions[idx];
	ft_printf("Instruction: %c  Facing: %c\n", cmd, game->player.facing);

	if (cmd == 'u')
		move_ship_forward(game);
	else if (cmd == 'l')
		game->player.facing = rotate_facing_left(game->player.facing);
	else if (cmd == 'r')
		game->player.facing = rotate_facing_right(game->player.facing);
	/* añade aquí más casos si tienes otros comandos */

	/* 4) Avanza el índice */
	game->instruction_index++;
}

/*
 * Engancha step_instruction al bucle principal de MLX
 * e inicia el proceso de ejecución paso a paso de las instrucciones.
 */
void execute_instructions(t_game *game)
{
	size_t len = ft_strlen(game->instructions);

	if (len == 0)
	{
		ft_printf("No instructions given\n");
		return;
	}

	game->instruction_index = 0;
	game->running           = 1;
	accumulator             = 0.0;
	mlx_loop_hook(game->mlx, &step_instruction, game);
}
