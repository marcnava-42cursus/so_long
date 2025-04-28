/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_renderer_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:29:59 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 19:06:24 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

mlx_image_t	*render_moves(t_game *game)
{
	char	*str;
	char	*moves;

	moves = ft_itoa(game->moves);
	if (!moves)
		return (NULL);
	str = ft_strjoin("Moves: ", moves);
	ft_free((void **)&moves);
	if (!str)
		return (NULL);
	if (game->moves_image)
		mlx_delete_image(game->mlx, game->moves_image);
	game->moves_image = mlx_put_string(game->mlx, str, 10, 10);
	return (ft_free((void **)&str), (void *)1);
}

mlx_image_t	*render_instructions(t_game *game)
{
	char	*str;
	char	*instructions;

	instructions = ft_strdup(game->instructions);
	if (!instructions)
		return (NULL);
	str = ft_strjoin("Instructions: ", instructions);
	ft_free((void **)&instructions);
	if (!str)
		return (NULL);
	if (game->instr_image)
		mlx_delete_image(game->mlx, game->instr_image);
	game->instr_image = mlx_put_string(game->mlx, str,
			10, (game->map->height * TILE_SIZE) + (7 * TILE_SIZE) - 44);
	ft_free((void **)&str);
	return ((void *)1);
}
