/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:06:56 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/25 21:07:44 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	add_instruction(t_game *game, char tile)
{
	size_t len;
	char *new_instr;

	len = ft_strlen(game->instructions);
	new_instr = malloc(len + 2);
	if (new_instr == NULL)
		return;

	ft_memcpy(new_instr, game->instructions, len);
	new_instr[len] = tile;
	new_instr[len + 1] = '\0';

	free(game->instructions);
	game->instructions = new_instr;
	ft_printf("Instructions: %s\n", game->instructions);
}

void	remove_instruction(t_game *game)
{
	size_t len;

	len = ft_strlen(game->instructions);
	if (len == 0)
		return;
	game->instructions[len - 1] = '\0';
	ft_printf("Instructions: %s\n", game->instructions);
}
