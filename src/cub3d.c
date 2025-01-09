/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/09 17:19:27 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->x = 0;
	cub->y = 0;
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
	cub->map = NULL;
	cub->gnl_free = 0;
	cub->cub_info = NULL;
	cub->mlx_ptr = NULL;
	cub->win_ptr = NULL;
	//cub->img_ptr = NULL;
}

void	print_cub(t_cub *cub)
{
	printf("\n---------------\nEXTRACTED INFO in struct :\n");
	if (cub->path[NO])
		printf("cub->path[NO]:   [%s]\n", cub->path[NO]);
	if (cub->path[SO])
		printf("cub->path[SO]:   [%s]\n", cub->path[SO]);
	if (cub->path[EA])
		printf("cub->path[EA]:   [%s]\n", cub->path[EA]);
	if (cub->path[WE])
		printf("cub->path[WE]:   [%s]\n", cub->path[WE]);
	if (cub->floor[0] != -1)
		printf("cub->floor[3]:   {%d, %d, %d}\n", cub->floor[0], cub->floor[1], cub->floor[2]);
	if (cub->ceiling[0] != -1)
		printf("cub->ceiling[3]: {%d, %d, %d}\n", cub->ceiling[0], cub->ceiling[1], cub->ceiling[2]);
	if (cub->map)
	{
		int i = 0;
		printf("\nMAP\ncub->height:     %d\n", cub->height);
		printf("cub->width:      %d\n", cub->width);
		printf("cub->map[y][x]:\n");
		while (cub->map[i])
		{
			printf("%.2d  [%s]\n", i, cub->map[i]);
			i++;
		}
		printf("XX  NULL-terminated\n");
	}
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (printf("Error\n%sMap file not found\n%s", MAUVE, END), 0);
	init_cub(&cub);
	parsing(argc, argv[1], &cub);
	print_cub(&cub);
	start_game(&cub);
	// 	cub.mlx = mlx_init(cub.width, cub.height, "cub3D", true);
	// 	if (!(cub.mlx))
	// 		clean_close(ERROR_MLX, &cub, 1);
	// 	render_background(&cub);
	// 	render_player(&cub, -1, 1);
	// 	mlx_key_hook(cub.mlx, &keyhook, &cub);
	// 	mlx_loop(cub.mlx);
	// 	ft_printf(CROSS_EXIT);
	printf("Game ended\n");
	return (0);
	//return (clean_close(NULL, &cub, 0));
}
