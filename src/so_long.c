/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:52:54 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/28 22:50:43 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_path>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (init_game(&game, argv[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	mlx_key_hook(game.mlx, &key_pressed_handler, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
