/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:41:18 by marcnava          #+#    #+#             */
/*   Updated: 2024/12/13 22:20:30 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int32_t	main(void)
{
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, TITLE, true);
	if (!mlx)
		error();

	xpm_t* xpm = mlx_load_xpm42("./ship.xpm42");
	if (!xpm)
		error();

	mlx_image_t* img = mlx_texture_to_image(mlx, &xpm->texture);
	if (!img)
		error();

	if (mlx_image_to_window(mlx, img, WIDTH / 2 - TILESIZE / 2, HEIGHT / 2 - TILESIZE / 2) < 0)
		error();

	mlx_loop(mlx);

	mlx_delete_image(mlx, img);
	mlx_delete_xpm42(xpm);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
