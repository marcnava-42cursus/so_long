/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:49:15 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 23:48:45 by marcnava         ###   ########.fr       */
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

# define MAX_MAP_SIZE 201

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

// Control

int			push_block(t_game *game, int dx, int dy);
int			can_ship_move(t_game *game, int x, int y);
int			in_bounds(t_game *game, int x, int y);
void		clear_cell(t_game *game, int x, int y);
void		draw_tile(t_game *game, int x, int y, char tile);
void		generate_block(t_game *game, int x, int y, char gen_tile);
void		add_instruction(t_game *game, char tile);
void		remove_instruction(t_game *game);
int			can_move(t_game *game, int nx, int ny);
int			handle_wall(char tile);
int			is_pushable(char tile);
int			is_generator(char tile);
char		door_for(char tile);
char		rotate_facing_right(char current);
char		rotate_facing_left(char current);
void		handle_delete_button(t_game *game, char tile);
void		handle_push_tile(t_game *game, char tile, int dx, int dy);
void		maybe_generate(t_game *game, char tile, int nx, int ny);
void		restore_previous(t_game *game, int ox, int oy);
void		update_prev_tile(t_game *game, char tile);
void		apply_tile_effects(t_game *game, char tile, int dx, int dy);
char		determine_sprite(int dx, int dy);
void		finalize_baba_move(t_game *game, int nx, int ny, char sprite);
int			move_baba(t_game *game, int dx, int dy);

// Execution

int			move_ship(t_game *game, int dx, int dy);
void		move_ship_forward(t_game *game);
void		execute_instructions(t_game *game);
char		get_ship_tile(char facing);
int			finalize_move(t_game *game);
void		perform_move(t_game *game, int new_x, int new_y);
int			handle_destination(t_game *game, int new_x, int new_y);
int			check_boundaries(t_game *game, int x, int y);
int			check_coins(t_game *game);

// Input

void		handle_rotation(t_game *game, char cmd);
void		execute_command(t_game *game, char cmd);
void		key_pressed_handler(mlx_key_data_t kd, void *param);
void		step_instruction(void *param);
void		handle_key(mlx_key_data_t kd, void *param);

// Map

void		flood_fill(char **map, int x, int y);
int			find_player_and_fill_map(char **map_copy, t_map *map);
int			check_reachable_items(char **map_copy, t_map *map);
int			check_valid_path(t_map *map);
char		**clone_map(char **map, int height);
int			clone_map_and_check(t_map *map, char ***map_copy);
int			map_errors(int p, int c, int e);
int			has_ber_extension(char *filename);
int			count_elements(t_map *map, int *p_count, int *e_count,
				int *c_count);
int			check_min_width(t_map *map);
int			validate_map(t_map *map);
int			check_row_widths(t_map *map);
int			check_walls(t_map *map);
int			allocate_map_memory(t_map **map, char ***temp_map,
				size_t max_lines);
void		allocate_baba_map_memory(t_map *map);
int			load_temp_map(char *map_path, t_map **map, char ***temp_map,
				size_t *lines_read);
int			add_row(char **temp_map, char *line, size_t idx);
int			validate_extension(char *map_path);
int			open_map_file(char *map_path, int *fd);
size_t		strip_newline(char *line);
size_t		parse_map(t_game *game, char *map_path);
int			read_map_lines(int fd, char **temp_map);
int			finalize_map(t_game *game, t_map *map, char **temp_map,
				size_t lines_read);

// Render

char		compute_baba_tile(t_game *game, size_t row, size_t col);
void		render_baba_cell(t_game *game, size_t row, size_t col);
void		render_baba(t_game *game);
void		*draw_baba_cell(t_game *game, size_t col, size_t row,
				char tile_char);
void		render_map(t_game *game);
void		*draw_cell(t_game *game, size_t row, size_t col);
char		*build_texture_path(char c);
xpm_t		*load_cell_xpm(char c);
void		handle_player(t_game *game, char c, size_t row, size_t col);
mlx_image_t	*create_cell_image(t_game *game, xpm_t *xpm);
int			place_cell_image(t_game *game, mlx_image_t *img, size_t row,
				size_t col);
mlx_image_t	*render_moves(t_game *game);
mlx_image_t	*render_instructions(t_game *game);

// Utils

int			is_debug_key(keys_t key);
void		append_instruction_char(char *instr, char c);
void		handle_backspace(char *instr);
void		process_debug_key(mlx_key_data_t kd, t_game *game);
void		debug_instructions(mlx_key_data_t kd, void *param);
void		free_image_map(void **map, size_t count);
void		cleanup_map(t_game *game);
void		cleanup_and_exit(t_game *game);
int			allocate_image_map(t_map *map);
int			allocate_baba_image_map(t_map *map);
size_t		init_game(t_game *game, char *map_path);

#endif