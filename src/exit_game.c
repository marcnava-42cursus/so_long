/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:00:53 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/01 16:39:08 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	cleanup_map(t_game *game)
{
	ft_free_matrix((void **)game->map->map);
	ft_free((void **)&game->map);
}

static void cleanup_textures(t_game *game)
{
	if (game->textures->exit)
		mlx_delete_image(game->mlx, game->textures->exit);
	if (game->textures->wall)
		mlx_delete_image(game->mlx, game->textures->wall);
	if (game->textures->floor)
		mlx_delete_image(game->mlx, game->textures->floor);
	if (game->textures->player)
		mlx_delete_image(game->mlx, game->textures->player);
	if (game->textures->collect)
		mlx_delete_image(game->mlx, game->textures->collect);
	ft_free((void **)&game->textures);
}

void cleanup_and_exit(t_game *game)
{
	if (game->textures)
		cleanup_textures(game);
	if (game->map)
		cleanup_map(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
