/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:00:44 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 06:54:33 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	generate_block(t_game *game,int y,int x,char tile)
{
	int door_x;char door;
	door_x = x + 1;
	if (door_x >= (int)game->map->width)
		return;
	if (tile == '4')
		door = 'l';
	else if (tile == '5')
		door = 'r';
	else if (tile == '6')
		door = 'u';
	else
		door = 'b';
	game->map->baba_map[y][door_x] = door;
	if (game->map->baba_image_map[y][door_x])
	{
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[y][door_x]);
		game->map->baba_image_map[y][door_x] = NULL;
	}
	draw_baba_cell(game, door_x, y, door);
}

static void	push_block(t_game *game,int y,int x,int dx,int dy)
{
	int bx,by;char tile;
	bx = x + dx;
	by = y + dy;
	if (bx < 0 || by < 0
		|| bx >= (int)game->map->width || by > 6
		|| game->map->baba_map[by][bx] != '8')
	{
		game->map->baba_map[y][x] = '8';
		if (game->map->baba_image_map[y][x])
		{
			mlx_delete_image(game->mlx,
				game->map->baba_image_map[y][x]);
			game->map->baba_image_map[y][x] = NULL;
		}
		draw_baba_cell(game, x, y, '8');
		return;
	}
	tile = game->map->baba_map[y][x];
	game->map->baba_map[by][bx] = tile;
	if (game->map->baba_image_map[by][bx])
	{
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[by][bx]);
		game->map->baba_image_map[by][bx] = NULL;
	}
	draw_baba_cell(game, bx, by, tile);
	game->map->baba_map[y][x] = '8';
	if (game->map->baba_image_map[y][x])
	{
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[y][x]);
		game->map->baba_image_map[y][x] = NULL;
	}
	draw_baba_cell(game, x, y, '8');
}

static int	move_baba(t_game *game,int dx,int dy)
{
	int old_x,old_y,new_x,new_y;char tile;
	old_x = game->player.baba_x;
	old_y = game->player.baba_y;
	new_x = old_x + dx;
	new_y = old_y + dy;
	if (new_x < 0 || new_y < 0
		|| new_x >= (int)game->map->width || new_y > 6)
		return (ft_printf("You are in the border, cannot move\n"), 0);
	tile = game->map->baba_map[new_y][new_x];
	if (tile == 'l' || tile == 'r' || tile == 'u' || tile == 'b')
		push_block(game, new_y, new_x, dx, dy);
	if (game->prev_baba_tile == '0')
		game->prev_baba_tile = '8';
	game->map->baba_map[old_y][old_x] = game->prev_baba_tile;
	if (game->map->baba_image_map[old_y][old_x])
	{
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[old_y][old_x]);
		game->map->baba_image_map[old_y][old_x] = NULL;
	}
	draw_baba_cell(game, old_x, old_y,
		game->map->baba_map[old_y][old_x]);
	if (tile == '4' || tile == '5' || tile == '6' || tile == '7')
		generate_block(game, new_y, new_x, tile);
	game->prev_baba_tile = tile;
	game->map->baba_map[new_y][new_x] = 'p';
	if (game->map->baba_image_map[new_y][new_x])
	{
		mlx_delete_image(game->mlx,
			game->map->baba_image_map[new_y][new_x]);
		game->map->baba_image_map[new_y][new_x] = NULL;
	}
	draw_baba_cell(game, new_x, new_y,
		game->map->baba_map[new_y][new_x]);
	game->player.baba_x = new_x;
	game->player.baba_y = new_y;
	return (1);
}

// static int	move_baba(t_game *game, int dx, int dy)
// {
// 	int  old_x = game->player.baba_x;
// 	int  old_y = game->player.baba_y;
// 	int  new_x = old_x + dx;
// 	int  new_y = old_y + dy;
// 	char tile;
// 	char old_prev = game->prev_baba_tile;
// 	char to_restore;
// 	bool pushing, is_generator;

// 	/* Limites del mapa */
// 	if (new_x < 0 || new_y < 0
// 		|| new_x >= (int)game->map->width || new_y > 6)
// 	{
// 		ft_printf("You are in the border, cannot move\n");
// 		return (0);
// 	}

// 	tile = game->map->baba_map[new_y][new_x];
// 	pushing      = (tile == 'l' || tile == 'r' || tile == 'u' || tile == 'b');
// 	is_generator = (tile == '4' || tile == '5' || tile == '6' || tile == '7');

// 	/* 1) Si empujamos, movemos primero el bloque */
// 	if (pushing)
// 		push_block(game, new_y, new_x, dx, dy);

// 	/* 2) Determinar qué queda atrás: si empujamos, siempre '8', si no,
// 	      restauramos lo que teníamos en prev_baba_tile (tratando '0' como suelo) */
// 	if (pushing)
// 		to_restore = '8';
// 	else if (old_prev == '0')
// 		to_restore = '8';
// 	else
// 		to_restore = old_prev;

// 	/* 3) Pintar/restaurar la celda antigua */
// 	game->map->baba_map[old_y][old_x] = to_restore;
// 	if (game->map->baba_image_map[old_y][old_x])
// 	{
// 		mlx_delete_image(game->mlx,
// 			game->map->baba_image_map[old_y][old_x]);
// 		game->map->baba_image_map[old_y][old_x] = NULL;
// 	}
// 	draw_baba_cell(game, old_x, old_y,
// 		game->map->baba_map[old_y][old_x]);

// 	/* 4) Si entramos en un generador, lo activamos sin borrarlo */
// 	if (is_generator)
// 		generate_block(game, new_y, new_x, tile);

// 	/* 5) Preparar prev_baba_tile para la próxima vez:
// 	      - si es generador, lo guardamos para restaurarlo al salir
// 	      - en cualquier otro caso, suponemos suelo ('8') */
// 	if (is_generator)
// 		game->prev_baba_tile = tile;
// 	else
// 		game->prev_baba_tile = '8';

// 	/* 6) Dibujar al jugador en la nueva posición */
// 	game->map->baba_map[new_y][new_x] = 'p';
// 	if (game->map->baba_image_map[new_y][new_x])
// 	{
// 		mlx_delete_image(game->mlx,
// 			game->map->baba_image_map[new_y][new_x]);
// 		game->map->baba_image_map[new_y][new_x] = NULL;
// 	}
// 	draw_baba_cell(game, new_x, new_y,
// 		game->map->baba_map[new_y][new_x]);

// 	/* 7) Actualizar coordenadas del jugador */
// 	game->player.baba_x = new_x;
// 	game->player.baba_y = new_y;
// 	return (1);
// }

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
