/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:59:49 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 19:03:46 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	cleanup_map(t_game *game)
{
	ft_free_matrix((void **)game->map->map);
	ft_free((void **)&game->map);
}

static void	cleanup_textures(t_game *game)
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

void	cleanup_and_exit(t_game *game)
{
	if (game->textures)
		cleanup_textures(game);
	if (game->map)
		cleanup_map(game);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
