/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:53:57 by marcnava          #+#    #+#             */
/*   Updated: 2025/03/29 20:48:20 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_errors(int p, int c, int e)
{
	const char	*errors[] = {
		"Error: Map must have exactly 1 player (P), found %d\n",
		"Error: Map must have exactly 1 exit (E), found %d\n",
		"Error: Map must have at least 1 collectible (C), found %d\n"
	};

	if (p != 1)
		return (ft_printf(errors[0], p), 1);
	if (e != 1)
		return (ft_printf(errors[1], e), 1);
	if (c < 1)
		return (ft_printf(errors[2], c), 1);
	return (0);
}
