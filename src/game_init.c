/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:05:06 by marcnava          #+#    #+#             */
/*   Updated: 2025/01/21 15:24:20 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	game_init(t_game *game, char *map_path)
{
	ft_calloc(1, sizeof(t_game));
	game->map = read_map(game, map_path);
	game->mlx = mlx_init(512, 512, TITLE, true);
}
