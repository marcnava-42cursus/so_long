/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcnava <marcnava@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 22:57:39 by marcnava          #+#    #+#             */
/*   Updated: 2025/01/21 19:28:25 by marcnava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_map	*read_map(t_game *game, char *path)
{
	t_map	*map;
	int		fd;
	char	*line;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit(EXIT_FAILURE);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	line = "1";
	while (line != NULL)
	{
		line = get_next_line(fd);
		ft_printf("%s", line);
		free(line);
	}
	return (map);
}
