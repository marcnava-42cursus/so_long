/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baba_renderer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:31:00 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 19:02:07 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	compute_baba_tile(t_game *game, size_t row, size_t col)
{
	char	tile_char;
	size_t	width;

	width = game->map->width;
	if (col == 0 || col == width - 1 || row == 6)
		tile_char = '9';
	else if (col == 1 && row >= 1 && row <= 4)
		tile_char = row + 3 + '0';
	else if (col == width - 5 && row == 5)
	{
		tile_char = 'p';
		game->player.baba_x = col;
		game->player.baba_y = row;
	}
	else if (col == width - 4 && row == 5)
		tile_char = 'a';
	else if (col == width - 3 && row == 5)
		tile_char = '2';
	else if (col == width - 2 && row == 5)
		tile_char = '3';
	else
		tile_char = '8';
	return (tile_char);
}

void	render_baba_cell(t_game *game, size_t row, size_t col)
{
	char	tile_char;

	tile_char = compute_baba_tile(game, row, col);
	game->map->baba_map[row][col] = tile_char;
	draw_baba_cell(game, col, row, tile_char);
}

void	render_baba(t_game *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < 7)
	{
		col = 0;
		while (col < game->map->width)
		{
			render_baba_cell(game, row, col);
			col++;
		}
		row++;
	}
}

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
	game->map->baba_image_map[row][col] = img;
	if (mlx_image_to_window(game->mlx, img, col * TILE_SIZE,
			game->map->height * TILE_SIZE + row * TILE_SIZE) < 0)
		return (mlx_delete_xpm42(xpm), NULL);
	mlx_delete_xpm42(xpm);
	return ((void *)1);
}
