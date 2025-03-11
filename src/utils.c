/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:22:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/11 11:50:58 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_map_size(t_cub *cub, t_list *lst)
{
	int		map_height;
	int		map_width;

	map_height = 0;
	while (lst)
	{
		map_width = 0;
		while (((char *)lst->data)[map_width])
			map_width++;
		if (map_width > cub->width)
			cub->width = map_width;
		map_height++;
		lst = lst->next;
	}
	cub->height = map_height;
	return (1);
}
