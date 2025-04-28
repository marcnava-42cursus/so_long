/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:15 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 06:56:44 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../libs/libft/includes/libft.h"
# include "../libs/minilibx/include/MLX42/MLX42.h"

# define TITLE "So Big"

# define TILE_SIZE 64

# define KEY_NUMPAD_2 322
# define KEY_NUMPAD_4 324
# define KEY_NUMPAD_6 326
# define KEY_NUMPAD_8 328

# define BABA_NORTH 'p'
# define BABA_SOUTH 's'
# define BABA_WEST 't'
# define BABA_EAST 'q'

# define SHIP_NORTH 'P'
# define SHIP_SOUTH 'S'
# define SHIP_WEST 'T'
# define SHIP_EAST 'Q'

# define MAX_MAP_SIZE 1024

typedef struct s_map
{
	mlx_image_t	***ship_image_map;
	char		**ship_map;
	mlx_image_t	***baba_image_map;
	char		**baba_map;
	size_t		width;
	size_t		height;
}			t_map;

typedef struct s_player
{
	size_t	ship_x;
	size_t	ship_y;
	size_t	baba_x;
	size_t	baba_y;
	char	facing;
}			t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_player	player;
	char		*instructions;
	char		prev_baba_tile;
	size_t		moves;
	int			running;
	double		speed;
	int			instruction_index;
	float		instruction_timer;
	mlx_image_t	*moves_image;
	mlx_image_t	*instr_image;
}			t_game;

// Map checker

int			has_ber_extension(char *filename);
int			check_row_widths(t_map *map);
int			count_elements(t_map *map, int *p_count, int *e_count,
				int *c_count);
int			check_walls(t_map *map);
size_t		parse_map(t_game *game, char *map_path);
char		**clone_map(char **map, int height);
int			clone_map_and_check(t_map *map, char ***map_copy);

// Error handler

int			map_errors(int p, int c, int e);

// Utils

int			check_valid_path(t_map *map);
size_t		init_game(t_game *game, char *map_path);
size_t		parse_map(t_game *game, char *map_path);
void		cleanup_and_exit(t_game *game);
char		*build_texture_path(char c);
void		execute_instructions(t_game *game);
int			move_baba(t_game *game, int dx, int dy);
int			push_block(t_game *game, int dx, int dy);
void		add_instruction(t_game *game, char tile);
void		remove_instruction(t_game *game);
void		generate_block(t_game *game, int x, int y, char tile);

int			in_bounds(t_game *game, int x, int y);
void		clear_cell(t_game *game, int x, int y);
void		draw_tile(t_game *game, int x, int y, char tile);
int			is_generator(char tile);
int			is_pushable(char tile);
char		door_for(char tile);
char		rotate_facing_right(char current);
char		rotate_facing_left(char current);
int			can_ship_move(t_game *game, int x, int y);

void		step_instruction(void *param);
void		move_ship_forward(t_game *game);

void		debug_instructions(mlx_key_data_t kd, void *param);

// render	

void		render_map(t_game *game);
void		render_baba(t_game *game);
void		*draw_cell(t_game *game, size_t row, size_t col);
void		*draw_baba_cell(t_game *game, size_t col, size_t row,
				char tile_char);
char		get_ship_tile(char facing);
mlx_image_t	*render_moves(t_game *game);
mlx_image_t	*render_instructions(t_game *game);

// hooks

void		handle_key(mlx_key_data_t kd, void *param);

#endif