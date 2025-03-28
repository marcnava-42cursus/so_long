/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:18:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/28 22:30:01 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_textures(t_game *game)
{
	xpm_t	*xpm;

	game->textures = ft_calloc(1, sizeof(t_images));
	if (!game->textures)
		return (1);
	xpm = mlx_load_xpm42(WALL);
	if (!xpm)
		return (ft_printf("Error\nFailed to load wall texture\n"), 1);
	game->textures->wall = mlx_texture_to_image(game->mlx, &xpm->texture);
	xpm = mlx_load_xpm42(FLOOR);
	if (!xpm)
		return (ft_printf("Error\nFailed to load floor texture\n"), 1);
	game->textures->floor = mlx_texture_to_image(game->mlx, &xpm->texture);
	xpm = mlx_load_xpm42(PLAYER);
	if (!xpm)
		return (ft_printf("Error\nFailed to load player texture\n"), 1);
	game->textures->player = mlx_texture_to_image(game->mlx, &xpm->texture);
	xpm = mlx_load_xpm42(EXIT);
	if (!xpm)
		return (ft_printf("Error\nFailed to load exit texture\n"), 1);
	game->textures->exit = mlx_texture_to_image(game->mlx, &xpm->texture);
	xpm = mlx_load_xpm42(COLLECTIBLE);
	if (!xpm)
		return (ft_printf("Error\nFailed to load collectible texture\n"), 1);
	game->textures->collect = mlx_texture_to_image(game->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	return (0);
}

void	draw_map(t_game *game)
{
	size_t		row;
	size_t		col;
	mlx_image_t	*img;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			if (game->map->map[row][col] == '1')
				img = game->textures->wall;
			else if (game->map->map[row][col] == 'P')
			{
				game->player.x = col;
				game->player.y = row;	
				img = game->textures->player;
			}
			else if (game->map->map[row][col] == 'E')
				img = game->textures->exit;
			else if (game->map->map[row][col] == 'C')
				img = game->textures->collect;
			else
				img = game->textures->floor;
			mlx_image_to_window(game->mlx, img, col * TILE_SIZE, row * TILE_SIZE);
			col++;
		}
		row++;
	}
}
