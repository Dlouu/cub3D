/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/18 16:21:29 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->x = 0;
	cub->y = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->floor[0] = -1;
	cub->floor[1] = -1;
	cub->floor[2] = -1;
	cub->ceiling[0] = -1;
	cub->ceiling[1] = -1;
	cub->ceiling[2] = -1;
	cub->map = NULL;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.fd = open("maps/map.cub", O_RDONLY);
	if (cub.fd == -1)
	{
		printf("%sError\n%s", MAUVE, END);
		printf("%s\n", strerror(errno));
	}
	init_cub(&cub);
	parsing(argc, argv[1], &cub);
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
