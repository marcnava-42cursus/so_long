/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:15:13 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 05:07:56 by marcnava         ###   ########.fr       */
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

static xpm_t	*load_cell_xpm(char c)
{
	char	*path;
	xpm_t	*xpm;

	path = build_texture_path(c);
	if (!path)
		return (NULL);
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
	{
		ft_printf("Error: Missing texture for char: %c\n", c);
		return (NULL);
	}
	return (xpm);
}

static void	handle_player(t_game *game, char c, size_t row, size_t col)
{
	if (c == 'P')
	{
		game->player.ship_x = col;
		game->player.ship_y = row;
	}
}

static mlx_image_t	*create_cell_image(t_game *game, xpm_t *xpm)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(game->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	return (img);
}

static int	place_cell_image(t_game *game, mlx_image_t *img,
	size_t row, size_t col)
{
	if (!img)
		return (-1);
	if (mlx_image_to_window(game->mlx, img, col * TILE_SIZE, row * TILE_SIZE)
		< 0)
		return (-1);
	return (0);
}

void	*draw_cell(t_game *game, size_t row, size_t col)
{
	char			c;
	xpm_t			*xpm;
	mlx_image_t		*img;
	int				res;

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
