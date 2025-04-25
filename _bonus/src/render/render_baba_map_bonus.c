/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_baba_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:52:20 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/24 20:15:04 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	*draw_baba_cell(t_game *game, size_t col, size_t row, char tile_char)
{
	char		*path;
	xpm_t		*xpm;
	mlx_image_t	*img;

	path = build_texture_path(tile_char);
	if (!path)
		return (NULL);
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
		return (NULL);
	img = mlx_texture_to_image(game->mlx, &xpm->texture);
	if (!img)
		return (mlx_delete_xpm42(xpm), NULL);
	ft_printf("w-h: %d-%d\n", game->map->width, game->map->height);
	game->map->baba_image_map[row][col] = img;
	if (mlx_image_to_window(game->mlx, img, col * TILE_SIZE,
			game->map->height * TILE_SIZE + row * TILE_SIZE) < 0)
		return (mlx_delete_xpm42(xpm), NULL);
	mlx_delete_xpm42(xpm);
	return ((void *)1);
}

void	render_baba(t_game *game)
{
	size_t	row;
	size_t	col;
	char	tile_char;

	row = 0;
	while (row < 7)
	{
		col = 0;
		while (col < game->map->width)
		{
			if (col == 0 || col == game->map->width - 1 || row == 6)
				tile_char = '9';
			else if (col == 1 && (row >= 1 && row <= 4))
				tile_char = (row + 3) + '0';
			else if (col == game->map->width - 5 && row == 5)
			{
				tile_char = 'p';
				game->player.baba_x = col;
				game->player.baba_y = row;
			}
			else if (col == game->map->width - 4 && row == 5)
				tile_char = 'a';
			else if (col == game->map->width - 3 && row == 5)
				tile_char = '2';
			else if (col == game->map->width - 2 && row == 5)
				tile_char = '3';
			else
				tile_char = '8';
			ft_printf("row-col: %d-%d\n", row, col);
			game->map->baba_map[row][col] = tile_char;
			draw_baba_cell(game, col, row, tile_char);
			col++;
		}
		row++;
	}
}
