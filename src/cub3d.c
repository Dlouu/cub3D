/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/16 17:03:04 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->map = NULL;
	cub->x = 0;
	cub->y = 0;
}

void	init_test(t_cub *cub)
{
	cub->no = ft_strdup("./path_to_the_north_texture", 0);
	cub->so = ft_strdup("./path_to_the_south_texture", 0);
	cub->ea = ft_strdup("./path_to_the_east_texture", 0);
	cub->we = ft_strdup("./path_to_the_west_texture", 0);
	cub->floor[0] = 220;
	cub->floor[1] = 100;
	cub->floor[2] = 0;
	cub->ceiling[0] = 225;
	cub->ceiling[1] = 30;
	cub->ceiling[2] = 0;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	(void)argc;
	ft_printf("%sHello World%s\n", MAUVE, END);
	cub.fd = open("maps/map.cub", O_RDONLY);
	//if ((cub.fd = open("maps/map.cub", O_RDONLY)) < 0)
	//	printf("open error\n");
	if (!strcmp(argv[1], "test"))
		init_test(&cub);
	else
	{
		init_cub(&cub);
		if (cub.fd == -1)
		{
			ft_printf("%sError\n%s", MAUVE, END);
			ft_printf("%s\n", strerror(errno));
		}
	}
	return (0);
}

//so long pour ref

// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	parsing(argc, argv[1], &game);
// 	if (game.width > 110 || game.height > 55)
// 		ft_error(ERROR_SIZE, &game);
// 	game.mlx = mlx_init(game.width * TILE, game.height * TILE, \
// 	"Pandakiwi", true);
// 	if (!(game.mlx))
// 		clean_close(ERROR_MLX, &game, 1);
// 	load_xpm(&game);
// 	xpm_to_image(&game, game.tile);
// 	render_background(&game);
// 	render_player(&game, -1, 1);
// 	mlx_key_hook(game.mlx, &keyhook, &game);
// 	mlx_loop(game.mlx);
// 	ft_printf(CROSS_EXIT);
// 	return (clean_close(NULL, &game, 0));
// }