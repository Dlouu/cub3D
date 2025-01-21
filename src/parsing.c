/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/21 15:52:18 by mbaumgar         ###   ########.fr       */
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

//actuellement je peux pas avoir de negatif car ils sont rejetes
//par la fonction is_valid_color_format, donc le check color < 0 inutile atm
//mais je le garde car maybe je vais changer la fonction
//is_valid_color_format avec les +

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

void	extract_line_info(t_cub *cub, char *line)
{
	int		i;

	i = skip_blank(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		cub->path[NO] = ft_strdup(line + i + 3, 0);
		if (!cub->path[NO])
			error_parsing("Malloc error");
		cub->path[NO] = ft_strtrim(cub->path[NO], " ", 0);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		cub->path[SO] = ft_strdup(line + i + 3, 0);
		if (!cub->path[SO])
			error_parsing("Malloc error");
		cub->path[SO] = ft_strtrim(cub->path[SO], " ", 0);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		cub->path[EA] = ft_strdup(line + i + 3, 0);
		if (!cub->path[EA])
			error_parsing("Malloc error");
		cub->path[EA] = ft_strtrim(cub->path[EA], " ", 0);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		cub->path[WE] = ft_strdup(line + i + 3, 0);
		if (!cub->path[WE])
			error_parsing("Malloc error");
		cub->path[WE] = ft_strtrim(cub->path[WE], " ", 0);
	}
	else if (line[i] == 'F')
		extract_color(ft_strtrim(line, " ", 0), cub->floor);
	else if (line[i] == 'C')
		extract_color(ft_strtrim(line, " ", 0), cub->ceiling);
}

void	extract_map(t_cub *cub, t_list *lst)
{
	t_list	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = lst;
	while (tmp)
	{
		if (j == 0)
		{
			while (((char *)tmp->data)[j])
				j++;
			cub->width = j;
		}
		i++;
		tmp = tmp->next;
	}
	cub->height = i;
	cub->map = walloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	while (lst)
	{
		cub->map[i] = ft_strdup(lst->data, 0);
		if (!cub->map[i])
			error_parsing("Malloc error");
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

void	extract_info_and_map(t_cub *cub)
{
	t_list	*lst;
	char	*line;
	int		i;
	t_list	*tmp;

	i = 0;
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
		lst = ft_lstnew(ft_strtrim(node, "\n", 0), 0);
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
	get_cub_file_info(cub);
	extract_info_and_map(cub);
	(void)map_file;
	return (0);
}

	// penser a limite la taille du jeu
	// exemple so long :
	// 	if (game.width > 110 || game.height > 55)
	// 		ft_error(ERROR_SIZE, &game);