/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:55:49 by marcnava          #+#    #+#             */
/*   Updated: 2024/12/13 21:57:13 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../libs/libft/headers/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

typedef struct	s_player
{
	mlx_image_t	sprite;
	int32_t		x;
	int32_t		y;
}	t_player;

#endif