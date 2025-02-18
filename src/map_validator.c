/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:57:07 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/02/18 13:55:07 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_player_position(t_cub *cub, char *str, int y)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'E' || str[i] == 'N' || str[i] == 'W' || str[i] == 'S')
		{
			if (str[i] == 'E')
				cub->dir = EA;
			if (str[i] == 'N')
				cub->dir = NO;
			if (str[i] == 'W')
				cub->dir = WE;
			if (str[i] == 'S')
				cub->dir = SO;
			cub->x = i;
			cub->y = y;
		}
		i++;
	}
}

t_coord	get_zero_position(char **map)
{
	t_coord	coord;

	coord.y = 0;
	while (map[coord.y])
	{
		coord.x = 0;
		while (map[coord.y][coord.x])
		{
			if (map[coord.y][coord.x] == '0')
				return (coord);
			coord.x++;
		}
		coord.y++;
	}
	return (coord);
}

void	flood_fill(t_cub *cub, char **map, t_coord pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= cub->width || pos.y >= cub->height)
		error_parsing("Map is not closed");
	if (map[pos.y][pos.x] == ' ')
		error_parsing("Map is not closed");
	if (map[pos.y][pos.x] == '1')
		return ;
	if (map[pos.y][pos.x] == '0')
	{
		map[pos.y][pos.x] = '.';
		flood_fill(cub, map, (t_coord){pos.x + 1, pos.y});
		flood_fill(cub, map, (t_coord){pos.x - 1, pos.y});
		flood_fill(cub, map, (t_coord){pos.x, pos.y + 1});
		flood_fill(cub, map, (t_coord){pos.x, pos.y - 1});
	}
}

void	check_valid_char_map(t_cub *cub, char *line, int y)
{
	int		i;

	i = 0;
	if (line[0] == '\0')
		error_parsing("Empty line in the map");
	while (line[i])
	{
		if (line[i] == '\n')
			error_parsing("Newline in the map");
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'E' && line[i] != 'N'
			&& line[i] != 'W' && line[i] != 'S')
			error_parsing("Invalid character in the map");
		if (line[i] == 'E' || line[i] == 'N'
			|| line[i] == 'W' || line[i] == 'S')
		{
			get_player_position(cub, line, y);
			cub->player++;
		}
		i++;
	}
}

void	map_validator(t_cub *cub)
{
	char	**map;

	if (cub->map == NULL)
		error_parsing("No map in the file");
	map = ft_strdup_array(cub->map, cub->height, 0);
	if (map == NULL)
		error_parsing("Malloc error while duplicating map");
	if (cub->player > 1)
		error_parsing("Multiple players in the map");
	flood_fill(cub, map, (t_coord){cub->x + 1, cub->y + 1});
	while (looking_for_zero(cub->height, map) == true)
		flood_fill(cub, map, get_zero_position(map));
	replace_blanks_by_walls(cub->map, cub->height, cub->width);
}
