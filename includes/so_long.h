/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:12:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 18:40:53 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

# ifndef LANG
#  define LANG "en-US"
# endif

# define PLAYER "/player.xpm42"
# define WALL "/wall.xpm42"
# define FLOOR "/floor.xpm42"
# define EXIT "/exit.xpm42"
# define COLLECTIBLE "/coin.xpm42"

# define TITLE "So Short"

# define TILE_SIZE 64

# define KEY_NUMPAD_2 322
# define KEY_NUMPAD_4 324
# define KEY_NUMPAD_6 326
# define KEY_NUMPAD_8 328

typedef struct s_map
{
	char	**ship_map;
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_images
{
	mlx_image_t	*exit;
	mlx_image_t	*wall;
	mlx_image_t	*floor;
	mlx_image_t	*player;
	mlx_image_t	*collect;
}	t_images;

typedef struct s_player
{
	size_t	ship_x;
	size_t	ship_y;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_images	*textures;
	t_player	player;
	int			moves;
}	t_game;

size_t	init_game(t_game *game, char *map_path);
size_t	parse_map(t_game *game, char *map_path);

void	print_map(t_map *map);
int		check_valid_path(t_map *map);
void	draw_map(t_game *game);
int		load_textures(t_game *game);
int		map_errors(int p, int c, int e);
void	cleanup_and_exit(t_game *game);
void	draw_tile(t_game *game, size_t row, size_t col);

void	key_pressed_handler(mlx_key_data_t keydata, void *param);
void	close_window_handler(void *param);

int		check_reachable_items(char **map_copy, t_map *map);
int		clone_map_and_check(t_map *map, char ***map_copy);
char	**clone_map(char **map, int height);

#endif