/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer_core_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:32:57 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 19:02:47 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	render_map(t_game *game)
{
	size_t	row;
	size_t	col;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			if (!draw_cell(game, row, col))
			{
				cleanup_and_exit(game);
				return ;
			}
			col++;
		}
		row++;
	}
}

void	*draw_cell(t_game *game, size_t row, size_t col)
{
	char		c;
	xpm_t		*xpm;
	mlx_image_t	*img;
	int			res;

	c = game->map->ship_map[row][col];
	xpm = load_cell_xpm(c);
	if (!xpm)
		return (NULL);
	handle_player(game, c, row, col);
	img = create_cell_image(game, xpm);
	if (!img)
		return (NULL);
	game->map->ship_image_map[row][col] = img;
	res = place_cell_image(game, img, row, col);
	if (res < 0)
		return (NULL);
	return ((void *)1);
}
