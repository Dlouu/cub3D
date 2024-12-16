/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/16 22:35:55 by mbaumgar         ###   ########.fr       */
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
	cub->map = malloc(sizeof(char) * 15);
	cub->map[0] = ft_strdup("        1111111111111111111111111\0", 0);
	cub->map[1] = ft_strdup("        1000000000110000000000001\0", 0);
	cub->map[2] = ft_strdup("        1011000001110000000000001\0", 0);
	cub->map[3] = ft_strdup("        1001000000000000000000001\0", 0);
	cub->map[4] = ft_strdup("111111111011000001110000000000001\0", 0);
	cub->map[5] = ft_strdup("100000000011000001110111111111111\0", 0);
	cub->map[6] = ft_strdup("11110111111111011100000010001\0", 0);
	cub->map[7] = ft_strdup("11110111111111011101010010001\0", 0);
	cub->map[8] = ft_strdup("11000000110101011100000010001\0", 0);
	cub->map[9] = ft_strdup("10000000000000001100000010001\0", 0);
	cub->map[10] = ft_strdup("10000000000000001101010010001\0", 0);
	cub->map[11] = ft_strdup("11000001110101011111011110N0111\0", 0);
	cub->map[12] = ft_strdup("11110111 1110101 101111010001\0", 0);
	cub->map[13] = ft_strdup("11111111 1111111 111111111111\0", 0);
	cub->map[14] = NULL;

}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
	{
		printf("%sError\n%s", MAUVE, END);
		printf("Usage: ./cub3d [map.cub]\n");
		return (0);
	}
	cub.fd = open("maps/map.cub", O_RDONLY);
	//if ((cub.fd = open("maps/map.cub", O_RDONLY)) < 0)
	//	printf("open error\n");
	if (!strcmp(argv[1], "test"))
	{
		init_test(&cub);
		game_test(&cub);
	}
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