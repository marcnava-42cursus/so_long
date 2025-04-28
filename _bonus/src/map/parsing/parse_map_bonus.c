/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:19:24 by marcnava          #+#    #+#             */
/*   Updated: 2025/04/28 18:56:36 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	validate_extension(char *map_path)
{
	if (!has_ber_extension(map_path))
	{
		ft_printf("Error: Invalid file extension. Expected .ber\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_map_file(char *map_path, int *fd)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd == -1)
	{
		ft_printf("Error: Failed to open map file\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

size_t	strip_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	return (len);
}

size_t	parse_map(t_game *game, char *map_path)
{
	t_map	*map;
	char	**temp_map;
	size_t	lines_read;
	int		status;

	ft_printf("Parsing map: %s\n", map_path);
	status = validate_extension(map_path);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	status = load_temp_map(map_path, &map, &temp_map, &lines_read);
	if (status == EXIT_FAILURE || lines_read <= 1)
		return (EXIT_FAILURE);
	status = finalize_map(game, map, temp_map, lines_read);
	if (status == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
