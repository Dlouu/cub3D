/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/13 12:28:45 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	error_parsing_close_fd(char *error, int fd)
{
	ft_printf("%sError\n%s", RED, END);
	ft_printf("%s%s\n%s", MAUVE, error, END);
	close(fd);
	exit(EXIT_FAILURE);
}

int	error_parsing(char *error)
{
	ft_printf("%sError\n%s", RED, END);
	ft_printf("%s%s\n%s", MAUVE, error, END);
	wclear(1);
	exit(EXIT_FAILURE);
}

static void	get_cub_file_info(t_cub *cub)
{
	t_list	*lst;
	char	*node;
	int		first_read;
	int		gnl_free;

	lst = NULL;
	first_read = 1;
	gnl_free = 0;
	while (1)
	{
		node = get_next_line(cub->fd, gnl_free, 0);
		if (!node && first_read == 1)
			error_parsing_close_fd("Empty file", cub->fd);
		first_read = 0;
		if (node == NULL)
			break ;
		lst = ft_lstnew(ft_strtrim_tail(node, "\n ", 0), 0);
		if (!lst)
		{
			gnl_free = 1;
			free(node);
			error_parsing_close_fd("Malloc failed", cub->fd);
		}
		ft_lstadd_back(&cub->cub_info, lst);
	}
}

void	parsing(int argc, char *map_file, t_cub *cub)
{
	if (argc != 2)
		error_parsing("Invalid number of arguments");
	if (!ft_strnstr(map_file, ".cub", ft_strlen(map_file)))
		error_parsing("Invalid file extension");
	get_cub_file_info(cub);
	close(cub->fd);
	extractor(cub, 0);
	validator(cub);
}
