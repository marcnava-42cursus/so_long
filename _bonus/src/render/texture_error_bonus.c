/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_error_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:31:52 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 20:34:35 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_texture_error(t_game *game, char missing)
{
	ft_printf("Error: Missing texture for char: %c\n", missing);
	cleanup_and_exit(game);
}
