/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:18:43 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/29 20:59:12 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	save_xpm_image(mlx_t *mlx, mlx_image_t **img, char *sprite)
{
	xpm_t	*xpm;
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(LANG, sprite);
	if (!tmp)
		return ;
	path = ft_strjoin("./textures/", tmp);
	ft_free((void **)&tmp);
	if (!path)
		return ;
	ft_printf("Loading sprite %s\n", path);
	xpm = mlx_load_xpm42(path);
	ft_free((void **)&path);
	if (!xpm)
	{
		ft_printf("Cannot load sprite %s\n", sprite);
		return ;
	}
	*img = mlx_texture_to_image(mlx, &xpm->texture);
	mlx_delete_xpm42(xpm);
}

int	load_textures(t_game *game)
{
	game->textures = ft_calloc(1, sizeof(t_images));
	if (!game->textures)
		return (1);
	save_xpm_image(game->mlx, &game->textures->wall, WALL);
	save_xpm_image(game->mlx, &game->textures->floor, FLOOR);
	save_xpm_image(game->mlx, &game->textures->player, PLAYER);
	save_xpm_image(game->mlx, &game->textures->exit, EXIT);
	save_xpm_image(game->mlx, &game->textures->collect, COLLECTIBLE);
	return (0);
}

static	mlx_image_t	*get_image_for_tile(char tile, t_game *game)
{
	if (tile == '1')
		return (game->textures->wall);
	else if (tile == 'P')
		return (game->textures->player);
	else if (tile == 'E')
		return (game->textures->exit);
	else if (tile == 'C')
		return (game->textures->collect);
	else
		return (game->textures->floor);
}

static void	update_player_position(char tile, size_t row, size_t col,
	t_game *game)
{
	if (tile == 'P')
	{
		game->player.x = col;
		game->player.y = row;
	}
}

void	draw_map(t_game *game)
{
	size_t		row;
	size_t		col;
	mlx_image_t	*img;
	char		tile;

	row = 0;
	while (row < game->map->height)
	{
		col = 0;
		while (col < game->map->width)
		{
			tile = game->map->map[row][col];
			update_player_position(tile, row, col, game);
			img = get_image_for_tile(tile, game);
			mlx_image_to_window(game->mlx, img, col * TILE_SIZE,
				row * TILE_SIZE);
			col++;
		}
		row++;
	}
}
