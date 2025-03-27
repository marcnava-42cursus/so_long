/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/27 17:44:41 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

size_t	init_game(t_game *game, char *map_path)
{
	// game->mlx = mlx_init(800, 600, TITLE, false);
	// if (!game->mlx)
	// {
	// 	ft_printf("Error\nFailed to initialize mlx\n");
	// 	return (EXIT_FAILURE);
	// }
	if (parse_map(game, map_path) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	free_map(t_map *map)
{
	while (*(map->map))
	{
		free(*(map->map));
		(map->map)++;
	}
	free(map);
}

void	free_game(t_game *game)
{
	free_map(game->map);
	mlx_terminate(game->mlx);
	free(game);
}
