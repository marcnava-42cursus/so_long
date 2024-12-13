/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:12:52 by marcnava          #+#    #+#             */
/*   Updated: 2024/12/13 21:55:40 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/headers/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

# define WIDTH 512
# define HEIGHT 512
# define TITLE "So Short"
# define TILESIZE 64

typedef struct s_game
{
	mlx_t	mlx;
	int32_t	w_width;
	int32_t	w_height;
}	t_game;

#endif