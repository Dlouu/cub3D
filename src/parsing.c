/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/04 10:37:31 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void extract_color(t_cub *cub, char *line)
{
	int		i;

	i = skip_blank(line);
	if (line[i] == 'F')
	{
		cub->floor[0] = ft_atoi(line + i + 1);
		cub->floor[1] = ft_atoi(line + i + 6);
		cub->floor[2] = ft_atoi(line + i + 10);
	}
	else if (line[i] == 'C')
	{
		cub->ceiling[0] = ft_atoi(line + i + 1);
		cub->ceiling[1] = ft_atoi(line + i + 6);
		cub->ceiling[2] = ft_atoi(line + i + 10);
	}
}

void	extract_line_info(t_cub *cub, char *line)
{
	int		i;

	i = skip_blank(line);
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		cub->path[NO] = ft_strdup(line + i + 3, 0);
		if (!cub->path[NO])
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		cub->path[SO] = ft_strdup(line + i + 3, 0);
		if (!cub->path[SO])
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'E' && line[i + 1] == 'A')
	{
		cub->path[EA] = ft_strdup(line + i + 3, 0);
		if (!cub->path[EA])
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		cub->path[WE] = ft_strdup(line + i + 3, 0);
		if (!cub->path[WE])
			printf("%sError Malloc\n%s", MAUVE, END);
	}
	else if (line[i] == 'F' || line[i] == 'C')
		extract_color(cub, line);
}

void	extract_map(t_cub *cub, t_list *lst)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	cub->map = walloc(sizeof(char *) * (i + 1), 1);
	i = 0;
	while (lst)
	{
		cub->map[i] = ft_strdup(lst->data, 0);
		if (!cub->map[i])
			printf("%sError Malloc\n%s", MAUVE, END);
		lst = lst->next;
		i++;
	}
	cub->map[i] = NULL;
}

int	map_detected(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

void	extract_info(t_cub *cub)
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
		if (map_detected(line[i]))
		{
			extract_map(cub, tmp);
			break ;
		}
		tmp = tmp->next;
	}
}

void	get_cub_info(t_cub *cub)
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
			printf("%sError empty\n%s", MAUVE, END);
		first_read = 0;
		if (node == NULL)
			break ;
		lst = ft_lstnew(ft_strtrim(node, "\n", 0), 0);
		if (!lst)
		{
			cub->gnl_free = 1;
			free(node);
			printf("%sError Malloc\n%s", MAUVE, END);
		}
		ft_lstadd_back(&cub->cub_info, lst);
	}
	extract_info(cub);
}

int	parsing(int argc, char *map_file, t_cub *cub)
{
	if (argc != 2)
	{
		printf("%sError\n%s", MAUVE, END);
		printf("%sToo many arguments\n%s", MAUVE, END);
		printf("Usage: ./cub3d [map.cub]\n");
		return (0);
	}
	get_cub_info(cub);
	(void)map_file;
	return (0);
}

	// penser a limite la taille du jeu
	// exemple so long :
	// 	if (game.width > 110 || game.height > 55)
	// 		ft_error(ERROR_SIZE, &game);