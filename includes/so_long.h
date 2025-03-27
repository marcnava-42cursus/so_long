/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:12:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/27 17:42:24 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

# define PLAYER "./assets/player.xpm42"
# define WALL "./assets/wall.xpm42"
# define FLOOR "./assets/floor.xpm42"
# define EXIT "./assets/exit.xpm42"
# define COLLECTIBLE "./assets/collectible.xpm42"

# define TITLE "So Long"

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_game
{
	mlx_t	*mlx;
	t_map	*map;
}	t_game;

size_t	init_game(t_game *game, char *map_path);
size_t	parse_map(t_game *game, char *map_path);
void	free_map(t_map *map);
void	free_game(t_game *game);

void	print_map(t_map *map);
int		check_valid_path(t_map *map);

#endif