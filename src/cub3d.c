/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/12 10:08:13 by mbaumgar         ###   ########.fr       */
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

int	main(void)
{
	t_cub	cub;

	ft_printf("%sHello World%s\n", MAUVE, END);
	cub.fd = open("map.cub", O_RDONLY);
	init_cub(&cub);
	if (cub.fd == -1)
	{
		ft_printf("%sError\n%s", MAUVE, END);
		ft_printf("%s\n", strerror(errno));
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