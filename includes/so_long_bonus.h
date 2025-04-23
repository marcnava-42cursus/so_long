/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:15 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/23 02:54:25 by marcnava         ###   ########.fr       */
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
	mlx_image_t	***baba_image_map;
	char		**baba_map;
	size_t		width;
	size_t		height;
}	t_map;

typedef struct s_player
{
	size_t	x;
	size_t	y;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	player;
	size_t		moves;
}	t_game;

// Map checker

int		has_ber_extension(char *filename);
int		check_row_widths(t_map *map);
int		count_elements(t_map *map, int *p_count, int *e_count, int *c_count);
int		check_walls(t_map *map);
size_t	parse_map(t_game *game, char *map_path);
char	**clone_map(char **map, int height);
int		clone_map_and_check(t_map *map, char ***map_copy);

// Error handler

int		map_errors(int p, int c, int e);

// Utils

int		check_valid_path(t_map *map);
size_t	init_game(t_game *game, char *map_path);
size_t	parse_map(t_game *game, char *map_path);
void	cleanup_and_exit(t_game *game);
void	render_map(t_game *game);
void	render_baba(t_game *game);
char	*build_texture_path(char c);

// hooks

void	key_pressed_handler(mlx_key_data_t keydata, void *param);

#endif