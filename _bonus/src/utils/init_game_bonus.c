/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:44:29 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/29 02:50:30 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	allocate_image_map(t_map *map)
{
	size_t	i;

	map->ship_image_map = ft_calloc(map->height, sizeof(mlx_image_t **));
	if (!map->ship_image_map)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->ship_image_map[i] = ft_calloc(map->width, sizeof(mlx_image_t *));
		if (!map->ship_image_map[i])
		{
			while (i > 0)
			{
				i--;
				ft_free((void **)&map->ship_image_map[i]);
			}
			ft_free((void **)&map->ship_image_map);
			return (0);
		}
		i++;
	}
	return (1);
}

int	allocate_baba_image_map(t_map *map)
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

static void	message_and_cleanup(t_game *game, char *str)
{
	ft_printf("%s\n", str);
	cleanup_and_exit(game);
}

static void	initialize_all(t_game *game)
{
	game->instructions = ft_calloc(MAX_MAP_SIZE, sizeof(char));
	game->player.facing = 'n';
	game->prev_baba_tile = '8';
	game->moves = 0;
	game->running = 0;
	game->instruction_index = 0;
	game->instruction_timer = 0.0;
	game->speed = 0.5;
	game->moves_image = NULL;
	game->instr_image = NULL;
}

size_t	init_game(t_game *game, char *map_path)
{
	int32_t	screen_w = 42;
	int32_t	screen_h = 41;
	int32_t	req_w;
	int32_t	req_h;

	if (parse_map(game, map_path) == 1)
		exit(EXIT_FAILURE);
	req_w = game->map->width * TILE_SIZE;
	req_h = game->map->height * TILE_SIZE + 7 * TILE_SIZE;
	mlx_get_monitor_size(0, &screen_w, &screen_h);
	ft_printf("%d-%d : %d-%d\n", req_w, req_h, screen_w, screen_h);
	if (req_w > screen_w || req_h > screen_h)
		message_and_cleanup(game, "Error: Map bigger than current window");
	game->mlx = mlx_init(req_w, req_h, TITLE, false);
	if (!game->mlx)
		message_and_cleanup(game, "Error: Failed to initialize mlx");
	if (!allocate_image_map(game->map))
		cleanup_and_exit(game);
	if (!allocate_baba_image_map(game->map))
		cleanup_and_exit(game);
	return (initialize_all(game), EXIT_SUCCESS);
}
