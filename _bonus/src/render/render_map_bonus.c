/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:15:13 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:58:49 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static char	*get_texture_name(char c)
{
	if (c == '0')
		return (ft_strdup("floor"));
	if (c == '1')
		return (ft_strdup("wall"));
	if (c == 'E')
		return (ft_strdup("exit"));
	if (c == 'P')
		return (ft_strdup("player"));
	if (c == 'C')
		return (ft_strdup("coin"));
	return (ft_strdup((char[]){c, 0}));
}

static char	*build_texture_path(char c)
{
	char	*name;
	char	*path;
	char	*full;

	name = get_texture_name(c);
	if (!name)
		return (NULL);
	path = ft_strjoin("./textures/_bonus/", name);
	ft_free((void **)&name);
	if (!path)
		return (NULL);
	full = ft_strjoin(path, ".xpm42");
	ft_free((void **)&path);
	if (!full)
		return (NULL);
	return (full);
}

static void	*draw_cell(t_game *game, size_t y, size_t x)
{
	xpm_t		*xpm;
	char		*path;
	char		c;

	c = game->map->map[y][x];
	path = build_texture_path(c);
	if (!path)
		return (NULL);
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
		return (print_texture_error(game, c), NULL);
	game->map->image_map[y][x] = mlx_texture_to_image(game->mlx, &xpm->texture);
	mlx_delete_texture(&xpm->texture);
	mlx_delete_xpm42(xpm);
	if (!game->map->image_map[y][x])
		return (NULL);
	if (mlx_image_to_window(game->mlx,
			game->map->image_map[y][x], x * 32, y * 32) < 0)
		return (NULL);
	return ((void *)1);
}

void	render_map(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (!draw_cell(game, y, x))
				cleanup_and_exit(game);
			x++;
		}
		y++;
	}
}
