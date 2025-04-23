/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_baba_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:52:20 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/23 16:39:20 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	draw_baba_tile(t_game *game, size_t col, size_t row, char tile_char)
{
	char *path;
	xpm_t *xpm;
	path = build_texture_path(tile_char);
	if (!path)
		return ;
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
		return ;
	if (mlx_image_to_window(game->mlx,
			mlx_texture_to_image(game->mlx, &xpm->texture),
			col * TILE_SIZE,
			game->map->height * TILE_SIZE + row * TILE_SIZE) < 0)
	{
		mlx_delete_xpm42(xpm);
		return ;
	}
	mlx_delete_xpm42(xpm);
}

void render_baba(t_game *game)
{
	size_t row;
	size_t col;
	char   tile_char;

	row = 0;
	while (row < 7)
	{
		col = 0;
		while (col < game->map->width)
		{
			if (col == 0 || col == game->map->width - 1 || row == 6)
				tile_char = '9';
			else if (col == 1 && (row >= 1 && row <= 4))
				tile_char = (char)(row + 3 + '0');
			else if (row == 5 && col >= game->map->width - 5 && col <= game->map->width - 2)
			{
				const char seq[] = { 'p', 'a', '2', '3' };
				tile_char = seq[col - (game->map->width - 5)];
			}
			else
				tile_char = '8';
			draw_baba_tile(game, col, row, tile_char);
			game->map->baba_map[row][col] = tile_char;

			col++;
		}
		row++;
	}
}
