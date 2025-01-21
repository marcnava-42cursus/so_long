/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:41:18 by marcnava          #+#    #+#             */
/*   Updated: 2025/01/21 15:25:35 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int32_t	main(int argc, char **argv)
{
	t_game	*game;

	if (argc == 2)
		game_init(game, argv[1]);
	return (EXIT_SUCCESS);
}
