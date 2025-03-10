/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/10 15:11:56 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_parsing(char *error)
{
	printf("%sError\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	wclear(1);
	exit(EXIT_FAILURE);
}

static void	get_cub_file_info(t_cub *cub)
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
	close(cub->fd);
	extract_info_and_map(cub, 0);
	map_validator(cub);
	if (cub->player == 0)
		error_parsing("No player in the map");
	if (cub->width * cub->height > 5000)
		error_parsing("Map too big");
	return (0);
}
