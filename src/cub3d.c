/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/08 09:35:43 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->x = -1;
	cub->y = -1;
	cub->dir = -1;
	cub->f_color = -1;
	cub->c_color = -1;
	cub->floor[0] = -1;
	cub->floor[1] = -1;
	cub->floor[2] = -1;
	cub->ceiling[0] = -1;
	cub->ceiling[1] = -1;
	cub->ceiling[2] = -1;
	cub->height = -1;
	cub->width = -1;
}

void	print_map(t_cub *cub, char **map)
{
	int	i;

	i = 0;
	printf("cub->height:     %d\n", cub->height);
	printf("cub->width:      %d\n", cub->width);
	printf("cub->map[y][x]:\n");
	while (i < cub->height)
	{
		printf("%.2d  [%s]\n", i, map[i]);
		i++;
	}
	printf("XX  NULL-terminated\n");
}

void	print_cub(t_cub *cub)
{
	if (cub->path[EA])
		printf("cub->path[EA]:   [%s]\n", cub->path[EA]);
	if (cub->path[NO])
		printf("cub->path[NO]:   [%s]\n", cub->path[NO]);
	if (cub->path[WE])
		printf("cub->path[WE]:   [%s]\n", cub->path[WE]);
	if (cub->path[SO])
		printf("cub->path[SO]:   [%s]\n", cub->path[SO]);
	if (cub->floor[0] != -1)
		printf("cub->floor[3]:   {%d, %d, %d}\n", cub->floor[0],
			cub->floor[1], cub->floor[2]);
	if (cub->ceiling[0] != -1)
		printf("cub->ceiling[3]: {%d, %d, %d}\n", cub->ceiling[0],
			cub->ceiling[1], cub->ceiling[2]);
	if (cub->dir != -1)
		printf("cub->dir:        %d\n", cub->dir);
	printf("cub->y.x:        %d.%d\n", cub->y, cub->x);
	if (cub->map)
		print_map(cub, cub->map);
	printf("c_color:         %d\n", cub->c_color);
	printf("f_color:         %d\n", cub->f_color);
}

int	main(int argc, char **argv)
{
	static t_cub	cub = {0};

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (printf("Error\n%sMap file not found\n%s", MAUVE, END), 0);
	init_cub(&cub);
	parsing(argc, argv[1], &cub);
	print_map(&cub, cub.map);
	start_game(&cub);
	printf("Game ended\n");
	wclear(0);
	return (0);
}
