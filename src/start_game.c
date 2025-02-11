/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/11 21:36:58 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_cub *cub, char *error, int status)
{
	printf("%sError\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
	wclear(1);
	exit(status);
}

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	ft_init_map(cub);
	ft_draw_rays(cub);
	ft_draw_walls(cub);
	ft_collision(cub);
}

int	start_game(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		return (close_game(cub, "mlx_init failed", 1));
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (close_game(cub, "mlx_new_image failed", 1));
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (close_game(cub, "mlx_image_to_window failed", 1));
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
