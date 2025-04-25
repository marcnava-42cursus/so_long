/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:44:29 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 03:27:55 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	allocate_image_map(t_map *map)
{
	size_t	i;

	map->image_map = ft_calloc(map->height, sizeof(mlx_image_t **));
	if (!map->image_map)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->image_map[i] = ft_calloc(map->width, sizeof(mlx_image_t *));
		if (!map->image_map[i])
		{
			while (i > 0)
			{
				i--;
				ft_free((void **)&map->image_map[i]);
			}
			ft_free((void **)&map->image_map);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	allocate_baba_image_map(t_map *map)
{
	size_t	i;

	map->baba_image_map = ft_calloc(7, sizeof(mlx_image_t **));
	if (!map->baba_image_map)
		return (0);
	i = 0;
	while (i < 7)
	{
		map->baba_image_map[i] = ft_calloc(map->width, sizeof(mlx_image_t *));
		if (!map->baba_image_map[i])
		{
			while (i > 0)
			{
				i--;
				ft_free((void **)&map->baba_image_map[i]);
			}
			ft_free((void **)&map->baba_image_map);
			return (0);
		}
		i++;
	}
	return (1);
}

size_t	init_game(t_game *game, char *map_path)
{
	if (parse_map(game, map_path) == 1)
		exit(EXIT_FAILURE);
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
			(game->map->height * TILE_SIZE) + 7 * TILE_SIZE, TITLE, false);
	if (!allocate_image_map(game->map))
		cleanup_and_exit(game);
	if (!allocate_baba_image_map(game->map))
		cleanup_and_exit(game);
	game->moves = 0;
	game->prev_baba_tile = '0';
	return (EXIT_SUCCESS);
}
