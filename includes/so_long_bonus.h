/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:15 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:43:08 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

# define TITLE "So Big"

# define TILE_SIZE 64

# define PLAYER "/player.xpm42"
# define WALL "/wall.xpm42"
# define FLOOR "/floor.xpm42"
# define EXIT "/exit.xpm42"
# define COLLECTIBLE "/coin.xpm42"

typedef struct s_map
{
	mlx_image_t	***image_map;
	char		**map;
	size_t		width;
	size_t		height;
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
	size_t	x;
	size_t	y;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_images	*textures;
	t_player	player;
	size_t		moves;
}	t_game;

// Map checker

int		has_ber_extension(char *filename);
int		is_valid_char(char c);
int		check_row_widths(t_map *map);
int		count_elements(t_map *map, int *p_count, int *e_count, int *c_count);
int		check_walls(t_map *map);
size_t	parse_map(t_game *game, char *map_path);

// Error handler

int		map_errors(int p, int c, int e);
void	print_texture_error(t_game *game, char missing);

// Utils

int		check_valid_path(t_map *map);
size_t	init_game(t_game *game, char *map_path);
size_t	parse_map(t_game *game, char *map_path);
void	cleanup_and_exit(t_game *game);
void	render_map(t_game *game);

#endif