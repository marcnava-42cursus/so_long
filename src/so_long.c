/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:52:54 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/07 14:40:05 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_path>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (init_game(&game, argv[1]) == EXIT_FAILURE)
		cleanup_and_exit(&game);
	mlx_key_hook(game.mlx, &key_pressed_handler, &game);
	mlx_loop(game.mlx);
	mlx_close_hook(game.mlx, &close_window_handler, &game);
	cleanup_and_exit(&game);
	exit(EXIT_SUCCESS);
}
