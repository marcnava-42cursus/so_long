/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:15:02 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/06 19:16:13 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	has_ber_extension(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	return (len > 4 && !ft_strncmp(filename + len - 4, ".ber", 4));
}

/**
 * @brief Checks if a map character is valid for gameplay.
 *
 * This function is used during map loading and validation to ensure that
 * only recognized characters are accepted for gameplay logic.
 *
 * @param c The character to check.
 * @return 1 if the character is valid, 0 otherwise.
 *
 * @details Valid characters and their meaning:
 * | Character | Meaning                        |
 * |-----------|---------------------------------|
 * | '1'       | Wall                            |
 * | '0'       | Floor                           |
 * | 'P'       | Player starting position        |
 * | 'C'       | Collectible                     |
 * | 'E'       | Exit                            |
 * | 'N'       | Enemy                           |
 * | 'A'       | Instruction: Move forward       |
 * | 'L'       | Instruction: Turn left          |
 * | 'R'       | Instruction: Turn right         |
 * | 'X'       | Instruction: Loop               |
 * | 'S'       | Execute/Send instruction set    |
 * | 'D'       | Delete block                    |
 * | 'M'       | Clear instruction program       |
 * | 'G'       | Run program                     |
 * | 'a'       | Generator for block 'A'         |
 * | 'l'       | Generator for block 'L'         |
 * | 'r'       | Generator for block 'R'         |
 * | 'x'       | Generator for block 'X'         |
 */
int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == 'P' || c == 'C' || c == 'E'
		|| c == 'N'
		|| c == 'A' || c == 'L' || c == 'R' || c == 'X'
		|| c == 'S' || c == 'D' || c == 'M' || c == 'G'
		|| c == 'a' || c == 'l' || c == 'r' || c == 'x');
}

int	check_row_widths(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		if (ft_strlen(map->map[i]) != map->width)
		{
			ft_printf("Error: Map rows must have the same width\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	count_elements(t_map *map, int *p_count, int *e_count, int *c_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_char(map->map[i][j]))
				return (ft_printf("Error: Invalid character in map: %c\n",
						map->map[i][j]), 0);
			if (map->map[i][j] == 'P')
				(*p_count)++;
			if (map->map[i][j] == 'E')
				(*e_count)++;
			if (map->map[i][j] == 'C')
				(*c_count)++;
			j++;
		}
		i++;
	}
	return (1);
}

int	check_walls(t_map *map)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < map->width)
	{
		if (map->map[0][j] != '1' || map->map[map->height - 1][j] != '1')
		{
			ft_printf("Error: Map must be enclosed by walls (1)\n");
			return (0);
		}
		j++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
		{
			ft_printf("Error: Map must be enclosed by walls (1) at sides\n");
			return (0);
		}
		i++;
	}
	return (1);
}
