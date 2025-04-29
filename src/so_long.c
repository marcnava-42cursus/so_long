/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:52:54 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 02:26:31 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (argc != 2)
		return (ft_printf("Usage: %s <map_path>\n", argv[0]), EXIT_FAILURE);
	init_game(&game, argv[1]);
	mlx_key_hook(game.mlx, &key_pressed_handler, &game);
	mlx_close_hook(game.mlx, &close_window_handler, &game);
	mlx_loop(game.mlx);
	cleanup_and_exit(&game);
	return (EXIT_SUCCESS);
}
