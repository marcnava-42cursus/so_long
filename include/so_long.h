/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:12:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/01/20 21:05:01 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/headers/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"
# include "../libs/ft_printf/ft_printf.h"
# include "../libs/get_next_line/get_next_line_bonus.h"

# define PLAYER "./assets/player.xpm42"
# define WALL "./assets/wall.xpm42"
# define FLOOR "./assets/floor.xpm42"
# define EXIT "./assets/exit.xpm42"
# define COLLECTIBLE "./assets/collectible.xpm42"

# define TITLE "So Long"

typedef struct s_map
{
	char	**map;
	int32_t	width;
	int32_t	height;
}	t_map;

typedef struct s_game
{
	mlx_t	*mlx;
	t_map	*map;
}	t_game;

// map

t_map	*read_map(t_game *game, char *path);

// game

void	game_init(t_game *game, char *map_path);

#endif