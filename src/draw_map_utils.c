/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:28:04 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 19:39:33 by marcnava         ###   ########.fr       */
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
