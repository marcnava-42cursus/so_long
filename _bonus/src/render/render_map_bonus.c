/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:15:13 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 01:48:58 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*build_texture_path(char c)
{
	char	*path;
	char	*full;
	char	*temp;

	temp = ft_calloc(2, sizeof(char));
	if (!temp)
		return (NULL);
	temp[0] = c;
	path = ft_strjoin("./textures/_bonus/", temp);
	ft_free((void **)&temp);
	if (!path)
		return (NULL);
	full = ft_strjoin(path, ".xpm42");
	ft_free((void **)&path);
	if (!full)
		return (NULL);
	return (full);
}

void	*draw_cell(t_game *game, size_t row, size_t col)
{
	xpm_t		*xpm;
	char		*path;
	char		c;

	c = game->map->ship_map[row][col];
	path = build_texture_path(c);
	if (!path)
		return (NULL);
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
		return (ft_printf("Error: Missing texture for char: %c\n", c), NULL);
	if (c == 'P')
	{
		game->player.ship_x = col;
		game->player.ship_y = row;
	}
	game->map->ship_image_map[row][col] = mlx_texture_to_image(game->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	if (!game->map->ship_image_map[row][col])
		return (NULL);
	if (mlx_image_to_window(game->mlx, game->map->ship_image_map[row][col],
			col * TILE_SIZE, row * TILE_SIZE) < 0)
		return (NULL);
	return ((void *)1);
}

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
