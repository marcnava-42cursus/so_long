/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:34:10 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 19:05:31 by marcnava         ###   ########.fr       */
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

xpm_t	*load_cell_xpm(char c)
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

void	handle_player(t_game *game, char c, size_t row, size_t col)
{
	if (c == 'P')
	{
		game->player.ship_x = col;
		game->player.ship_y = row;
	}
}

mlx_image_t	*create_cell_image(t_game *game, xpm_t *xpm)
{
	mlx_image_t	*img;

	img = mlx_texture_to_image(game->mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
	return (img);
}

int	place_cell_image(t_game *game, mlx_image_t *img, size_t row, size_t col)
{
	if (!img)
		return (-1);
	if (mlx_image_to_window(game->mlx, img, col * TILE_SIZE, row * TILE_SIZE)
		< 0)
		return (-1);
	return (0);
}
