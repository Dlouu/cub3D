/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:57:07 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/13 12:28:53 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	replace_blanks_by_walls(char **map, int height, int width)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
			x++;
		}
		y++;
	}
}

static t_coord	get_zero_position(char **map)
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
	if (map[pos.y][pos.x] == '0'
		|| map[pos.y][pos.x] == 'N'
		|| map[pos.y][pos.x] == 'E'
		|| map[pos.y][pos.x] == 'S'
		|| map[pos.y][pos.x] == 'W')
	{
		map[pos.y][pos.x] = '.';
		flood_fill(cub, map, (t_coord){pos.x + 1, pos.y});
		flood_fill(cub, map, (t_coord){pos.x - 1, pos.y});
		flood_fill(cub, map, (t_coord){pos.x, pos.y + 1});
		flood_fill(cub, map, (t_coord){pos.x, pos.y - 1});
	}
}

void	validator(t_cub *cub)
{
	char	**map;

	if (cub->map == NULL)
		error_parsing("No map in the file");
	if (cub->player == 0)
		error_parsing("No player in the map");
	if (cub->player > 1)
		error_parsing("Multiple players in the map");
	map = ft_strdup_array(cub->map, cub->height, 0);
	if (map == NULL)
		error_parsing("Malloc error while duplicating map");
	flood_fill(cub, map, (t_coord){cub->x, cub->y});
	while (looking_for_zero(cub->height, map) == true)
		flood_fill(cub, map, get_zero_position(map));
	replace_blanks_by_walls(cub->map, cub->height, cub->width);
}
