/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:19:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 02:26:41 by marcnava         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
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
