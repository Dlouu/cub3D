/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:57:07 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/27 17:36:36 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//flood_fill(cub);

void	check_valid_char_map(t_cub *cub, char *line)
{
	if (line[0] == '\0')
		error_parsing("Empty line in the map");
	while (*line)
	{
		if (*line == '\n')
			error_parsing("Newline in the map");
		if (*line != ' ' && *line != '1' && *line != '0'
			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
			error_parsing("Invalid character in the map");
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			cub->player++;
		line++;
	}
	if (cub->player > 1)
		error_parsing("Multiple players in the map");
}
