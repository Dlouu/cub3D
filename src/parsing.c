/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/24 15:26:31 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	go_to_next_comma(char *line, int i)
{
	while (line[i] && line[i] != ',')
		i++;
	return (i);
}

int	skip_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	valid_char_info(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'C' || c == 'F')
		return (1);
	return (0);
}

int	error_parsing(char *error)
{
	printf("%sError:\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	wclear(1);
	exit(EXIT_FAILURE);
}

int	is_valid_color_format(char *line)
{
	int		i;
	int		comma;

	comma = 0;
	i = 1;
	i += skip_blank(line + i);
	while (line[i])
	{
		if (line[i] == ',')
		{
			if (line[i + 1] == ',' || line[i + 1] == '\0')
				return (error_parsing("Invalid color (missing number)"));
			if (i != 0 && line[i - 1] == ' ')
				return (error_parsing("Invalid color (missing number)"));
			comma++;
		}
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (error_parsing("Invalid color format"));
		i++;
	}
	if (comma != 2)
		return (error_parsing("Invalid color format (comma error)"));
	return (1);
}

void	extract_color(char *line, int *color)
{
	int	i;

	i = 1;
	if (!is_valid_color_format(line))
		return ;
	if (color[0] != -1)
		printf("%sError, color already set\n%s", RED, END);
	color[0] = ft_atoi(line + i + 1);
	i = go_to_next_comma(line, i);
	color[1] = ft_atoi(line + i + 1);
	i = go_to_next_comma(line, i + 1);
	color[2] = ft_atoi(line + i + 1);
	if (color[0] < 0 || color[1] < 0 || color[2] < 0)
		error_parsing("Invalid color value (no negative alowed)");
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		error_parsing("Invalid color value (255 max range)");
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
	if (!ft_strcmp(key, "NO"))
		return (NO);
	else if (!ft_strcmp(key, "SO"))
		return (SO);
	else if (!ft_strcmp(key, "EA"))
		return (EA);
	else if (!ft_strcmp(key, "WE"))
		return (WE);
	else if (!ft_strcmp(key, "F"))
		return (FLOOR);
	else if (!ft_strcmp(key, "C"))
		return (CEILING);
	return (-1);
}

void	extract_line_info(t_cub *cub, char *line)
{
	int		i;
	int		key;

	i = skip_blank(line);
	key = get_key(line, i);
	if (key == -1)
		return ;
	if (key == NO || key == SO || key == EA || key == WE)
	{
		cub->path[key] = ft_strdup(line + i + 3, 0);
		if (!cub->path[key])
			error_parsing("Malloc error in extract_line_info");
		cub->path[key] = ft_strtrim(cub->path[key], " ", 0);
		//if (open(cub->path[key], O_RDONLY) == -1)
		//	error_parsing("Invalid path in the .cub file");
	}
	else if (key == FLOOR)
		extract_color(ft_strtrim(line, " ", 0), cub->floor);
	else if (key == CEILING)
		extract_color(ft_strtrim(line, " ", 0), cub->ceiling);
}

int	get_map_size(t_cub *cub, t_list *lst)
{
	int		map_height;
	int		map_width;
	t_list	*tmp;

	map_height = 0;
	map_width = 0;
	tmp = lst;
	while (tmp)
	{
		while (((char *)tmp->data)[map_width])
			map_width++;
		if (map_width > cub->width)
			cub->width = map_width;
		map_height++;
		tmp = tmp->next;
	}
	cub->height = map_height;
	return (1);
}

void	extract_map(t_cub *cub, t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	cub->height = 14;
	get_map_size(cub, lst);
	cub->map = walloc(sizeof(char *) * (cub->height + 1), 0);
	if (!cub->map)
		error_parsing("Malloc error in extract_map");
	while (lst)
	{
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

int	map_detected(char c, t_cub *cub)
{
	if (c == '1')
	{
		if (!cub->path[NO])
			error_parsing("Missing north path in the .cub file");
		if (!cub->path[SO])
			error_parsing("Missing south path in the .cub file");
		if (!cub->path[EA])
			error_parsing("Missing east path in the .cub file");
		if (!cub->path[WE])
			error_parsing("Missing west path in the .cub file");
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
	t_list	*tmp;

	lst = cub->cub_info;
	tmp = lst;
	while (lst)
	{
		line = (char *)lst->data;
		i = skip_blank(line);
		if (valid_char_info(line[i]))
			extract_line_info(cub, &line[i]);
		lst = lst->next;
	}
	while (tmp)
	{
		line = (char *)tmp->data;
		i = skip_blank(line);
		if (map_detected(line[i], cub))
		{
			extract_map(cub, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	get_cub_file_info(t_cub *cub)
{
	t_list	*lst;
	char	*node;
	int		first_read;

	lst = NULL;
	first_read = 1;
	while (1)
	{
		node = get_next_line(cub->fd, cub->gnl_free, 0);
		if (!node && first_read == 1)
			error_parsing("Empty file");
		first_read = 0;
		if (node == NULL)
			break ;
		lst = ft_lstnew(ft_strtrim_tail(node, "\n ", 0), 0);
		if (!lst)
		{
			cub->gnl_free = 1;
			free(node);
			error_parsing("Malloc error");
		}
		ft_lstadd_back(&cub->cub_info, lst);
	}
}

int	parsing(int argc, char *map_file, t_cub *cub)
{
	if (argc != 2)
		error_parsing("Invalid number of arguments");
	if (!ft_strnstr(map_file, ".cub", ft_strlen(map_file)))
		error_parsing("Invalid file extension");
	get_cub_file_info(cub);
	extract_info_and_map(cub, 0);
	return (0);
}

	// penser a limiter la taille du jeu, en fonction de l'exe
	// voir avec Nils nombre de case possible ou x et y
	//flood fill tab qui check les 0 s'ilsont ete floodfilled
	//textures en commentaire car on en a pas encore xD
	//check valid char map
	//check nombre de joueurs