/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:13:05 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/10 13:40:37 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extract_line_info(t_cub *cub, char *line)
{
	int		i;
	int		key;
	int		fd;

	i = skip_blank(line);
	key = get_key(line, i);
	if (key == -1)
		return (error_parsing("Invalid key in the .cub file"), 1);
	if (key == NO || key == SO || key == EA || key == WE)
	{
		cub->path[key] = ft_strdup(line + i + 3, 0);
		if (!cub->path[key])
			error_parsing("Malloc error in extract_line_info");
		cub->path[key] = ft_strtrim(cub->path[key], " ", 0);
		fd = open(cub->path[key], O_RDONLY);
		close(fd);
		if (fd == -1)
			error_parsing("Invalid path in the .cub file");
	}
	else if (key == FLOOR)
		extract_color(ft_strtrim(line, " ", 0), cub->floor);
	else if (key == CEILING)
		extract_color(ft_strtrim(line, " ", 0), cub->ceiling);
	return (0);
}

static int	get_map_size(t_cub *cub, t_list *lst)
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

void	extract_map(t_cub *cub, t_list *lst)
{
	int		i;

	i = 0;
	get_map_size(cub, lst);
	cub->map = walloc(sizeof(char *) * (cub->height + 1), 0);
	if (!cub->map)
		error_parsing("Malloc error in extract_map");
	while (lst)
	{
		check_valid_char_map(cub, lst->data, i);
		cub->map[i] = walloc(sizeof(char) * (cub->width + 1), 0);
		ft_memset(cub->map[i], ' ', cub->width);
		ft_memcpy(cub->map[i], lst->data, ft_strlen(lst->data));
		cub->map[i][cub->width] = '\0';
		if (!cub->map[i])
			error_parsing("Malloc error in extract_map");
		lst = lst->next;
		i++;
	}
	cub->map[i] = NULL;
}

static int	map_detected(char c, t_cub *cub)
{
	if (c == '1')
	{
		if (!cub->path[EA])
			error_parsing("Missing east path in the .cub file");
		if (!cub->path[NO])
			error_parsing("Missing north path in the .cub file");
		if (!cub->path[WE])
			error_parsing("Missing west path in the .cub file");
		if (!cub->path[SO])
			error_parsing("Missing south path in the .cub file");
		if (cub->floor[0] == -1)
			error_parsing("Missing floor color in the .cub file");
		if (cub->ceiling[0] == -1)
			error_parsing("Missing ceiling color in the .cub file");
		return (1);
	}
	return (0);
}

void	extract_info_and_map(t_cub *cub, int i)
{
	t_list	*lst;
	char	*line;

	lst = cub->cub_info;
	while (lst)
	{
		line = (char *)lst->data;
		i = skip_blank(line);
		if (map_detected(line[i], cub))
		{
			extract_map(cub, lst);
			break ;
		}
		if (line[i] == '\n')
		{
			lst = lst->next;
			continue ;
		}
		extract_line_info(cub, &line[i]);
		lst = lst->next;
	}
}
