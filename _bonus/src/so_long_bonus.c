/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:19:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/27 07:15:36 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	print_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		ft_printf("%s\n", map[i]);
		i++;
	}
}

static void	debug_instructions(mlx_key_data_t kd, void *param)
{
	t_game	*game;
	size_t	len;

	game = (t_game *)param;
	if (kd.action != MLX_PRESS)
		return ;
	len = ft_strlen(game->instructions);
	if (len + 1 >= 1024)
		return ;
	if (kd.key == MLX_KEY_U)
		game->instructions[len] = 'u';
	else if (kd.key == MLX_KEY_L)
		game->instructions[len] = 'l';
	else if (kd.key == MLX_KEY_R)
		game->instructions[len] = 'r';
	else if (kd.key == MLX_KEY_B)
		game->instructions[len] = 'b';
	else if (kd.key == MLX_KEY_BACKSPACE)
	{
		if (len > 0)
			game->instructions[--len] = '\0';
	}
	else
		return ;
	game->instructions[len + 1] = '\0';
	ft_printf("Instructions: %s\n", game->instructions);
}

static void	handle_key(mlx_key_data_t kd, void *param)
{
	debug_instructions(kd, param);
	key_pressed_handler(kd, param);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (init_game(&game, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render_map(&game);
	render_baba(&game);
	print_map(game.map->ship_map);
	print_map(game.map->baba_map);
	mlx_key_hook(game.mlx, &handle_key, &game);
	mlx_loop_hook(game.mlx, &step_instruction, &game);
	mlx_loop(game.mlx);
	cleanup_and_exit(&game);
	return (0);
}
