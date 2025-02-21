/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:22:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/02/21 18:34:45 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 0x000000FF);
}

bool	looking_for_zero(int height, char **map)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

int	skip_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	get_key(char *line, int i)
{
	char	*key;
	int		len;

	len = 0;
	while (line[i + len] && line[i + len] != ' ')
		len++;
	key = ft_strndup(line + i, len + 1, 0);
	if (!key)
		error_parsing("Malloc error in get_key");
	if (!ft_strcmp(key, "EA"))
		return (EA);
	else if (!ft_strcmp(key, "NO"))
		return (NO);
	else if (!ft_strcmp(key, "WE"))
		return (WE);
	else if (!ft_strcmp(key, "SO"))
		return (SO);
	else if (!ft_strcmp(key, "F"))
		return (FLOOR);
	else if (!ft_strcmp(key, "C"))
		return (CEILING);
	else
		return (-1);
}

void	replace_blanks_by_walls(char **map, int height, int width)
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
