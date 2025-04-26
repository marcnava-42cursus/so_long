/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orientation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:00:38 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/26 21:04:37 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	rotate_facing_right(char current)
{
	if (current == 'n')
		return ('e');
	if (current == 'e')
		return ('s');
	if (current == 's')
		return ('w');
	return ('n');
}

char	rotate_facing_left(char current)
{
	if (current == 'n')
		return ('w');
	if (current == 'w')
		return ('s');
	if (current == 's')
		return ('e');
	return ('n');
}
