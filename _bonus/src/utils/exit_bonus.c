/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:59:49 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 19:10:41 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_image_map(void **map, size_t count)
{
	size_t	i;

	if (!map)
		return ;
	i = 0;
	while (i < count)
	{
		if (map[i])
			ft_free((void **)&map[i]);
		i++;
	}
	ft_free((void **)&map);
}

void	cleanup_map(t_game *game)
{
	if (game->map->ship_image_map)
		free_image_map((void **)game->map->ship_image_map,
			game->map->height);
	if (game->map->baba_image_map)
		free_image_map((void **)game->map->baba_image_map, 7);
	if (game->map->baba_map)
		ft_free_matrix((void **)game->map->baba_map);
	if (game->map->ship_map)
		free_image_map((void **)game->map->ship_map,
			MAX_MAP_SIZE);
	ft_free((void **)&game->map);
}

void	cleanup_and_exit(t_game *game)
{
	if (game->mlx)
		mlx_terminate(game->mlx);
	if (game->map)
		cleanup_map(game);
	if (game->instructions)
		ft_free((void **)&game->instructions);
	exit(EXIT_SUCCESS);
}
