/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/02/03 10:33:57 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//info
//cub->player_x = 0; ==> find player position
//cub->player_y = 0; ==> find player position
// la position du joueur est deja dans cub->x et cub->y
//cub->dir = NO or 0 = North, SO/1 = South, EA/2 = East, WE/2 = West (int)

void	init_game(t_cub *cub)
{
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	cub->offset_x = 0;
	cub->offset_y = 0;
	cub->player_x = 0;
	cub->player_y = 0;
	cub->move_left = 0;
	cub->move_right = 0;
	cub->move_bot = 0;
	cub->move_top = 0;
	cub->len_ray = 0;
	cub->rotation_angle = 0;
	cub->len_ray_bot = 0;
	cub->len_ray_top = 0;
	cub->len_ray_left = 0;
	cub->len_ray_right = 0;
}

void	init_cub(t_cub *cub)
{
	cub->x = -1;
	cub->y = -1;
	cub->player = 0;
	cub->dir = -1;
	cub->path[NO] = NULL;
	cub->path[SO] = NULL;
	cub->path[EA] = NULL;
	cub->path[WE] = NULL;
	cub->floor[0] = -1;
	cub->floor[1] = -1;
	cub->floor[2] = -1;
	cub->ceiling[0] = -1;
	cub->ceiling[1] = -1;
	cub->ceiling[2] = -1;
	cub->height = -1;
	cub->width = -1;
	cub->map = NULL;
	cub->gnl_free = 0;
	cub->cub_info = NULL;
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
	if (cub->path[NO])
		printf("cub->path[NO]:   [%s]\n", cub->path[NO]);
	if (cub->path[SO])
		printf("cub->path[SO]:   [%s]\n", cub->path[SO]);
	if (cub->path[EA])
		printf("cub->path[EA]:   [%s]\n", cub->path[EA]);
	if (cub->path[WE])
		printf("cub->path[WE]:   [%s]\n", cub->path[WE]);
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
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (printf("Error\n%sMap file not found\n%s", MAUVE, END), 0);
	init_cub(&cub);
	init_game(&cub);
	parsing(argc, argv[1], &cub);
	start_game(&cub);
	printf("Game ended\n");
	wclear(0);
	return (0);
}

//	print_cub(&cub);
