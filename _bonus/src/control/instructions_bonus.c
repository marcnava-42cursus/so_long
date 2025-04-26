/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:06:56 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 22:14:33 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	add_instruction(t_game *game, char tile)
{
	size_t	len;

	len = ft_strlen(game->instructions);
	game->instructions[len] = tile;
	ft_printf("Instructions: %s\n", game->instructions);
}

void	remove_instruction(t_game *game)
{
	size_t	len;

	len = ft_strlen(game->instructions);
	if (len == 0)
		return ;
	game->instructions[len - 1] = '\0';
	ft_printf("Instructions: %s\n", game->instructions);
}
