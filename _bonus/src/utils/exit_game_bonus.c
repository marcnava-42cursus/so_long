/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:59:49 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/27 16:46:24 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	cleanup_map(t_game *game)
{
	size_t	i;

	if (game->map->ship_image_map)
	{
		i = 0;
		while (i < game->map->height)
		{
			if (game->map->ship_image_map[i])
				ft_free((void **)&game->map->ship_image_map[i]);
			i++;
		}
		ft_free((void **)&game->map->ship_image_map);
	}
	if (game->map->baba_image_map)
	{
		i = 0;
		while (i < 7)
		{
			if (game->map->baba_image_map[i])
				ft_free((void **)&game->map->baba_image_map[i]);
			i++;
		}
		ft_free((void **)&game->map->baba_image_map);
	}
	if (game->map->baba_map)
		ft_free_matrix((void **)game->map->baba_map);
	if (game->map->ship_map)
	{
		i = 0;
		while (i < MAX_MAP_SIZE)
		{
			if (game->map->ship_map[i])
				ft_free((void **)&game->map->ship_map[i]);
			i++;
		}
		ft_free((void **)&game->map->ship_map);
	}
	ft_free((void **)&game->map);
}

void	cleanup_and_exit(t_game *game)
{
	if (game->map)
		cleanup_map(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
