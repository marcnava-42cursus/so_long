/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:19:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:37:08 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Usage: %s <map_path>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (init_game(&game, argv[1]) == EXIT_FAILURE)
		cleanup_and_exit(&game);
	render_map(&game);
	exit(EXIT_SUCCESS);
}
