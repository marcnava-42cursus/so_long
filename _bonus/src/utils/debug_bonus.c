/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:15:15 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/27 17:22:26 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_debug_key(keys_t key)
{
	if (key == MLX_KEY_U || key == MLX_KEY_L
		|| key == MLX_KEY_R || key == MLX_KEY_B)
		return (1);
	return (0);
}

static void	append_instruction_char(char *instr, char c)
{
	size_t	len;

	len = ft_strlen(instr);
	if (len < MAX_MAP_SIZE)
	{
		instr[len] = c;
		instr[len + 1] = '\0';
	}
}

static void	handle_backspace(char *instr)
{
	size_t	len;

	len = ft_strlen(instr);
	if (len > 0)
		instr[len - 1] = '\0';
}

static void	process_debug_key(mlx_key_data_t kd, t_game *game)
{
	char	c;

	if (kd.action != MLX_PRESS)
		return ;
	if (is_debug_key(kd.key))
	{
		if (kd.key == MLX_KEY_U)
			c = 'u';
		else if (kd.key == MLX_KEY_L)
			c = 'l';
		else if (kd.key == MLX_KEY_R)
			c = 'r';
		else
			c = 'b';
		append_instruction_char(game->instructions, c);
	}
	else if (kd.key == MLX_KEY_BACKSPACE)
		handle_backspace(game->instructions);
	else
		return ;
	ft_printf("Instructions: %s\n", game->instructions);
}

void	debug_instructions(mlx_key_data_t kd, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	process_debug_key(kd, game);
}
