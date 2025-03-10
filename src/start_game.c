/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/10 11:20:13 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_cub *cub)
{
	cub->east = mlx_load_png(cub->path[EA]);
	if (!cub->east)
		return (close_game(cub, "mlx_load_png EAST failed", 1));
	cub->north = mlx_load_png(cub->path[NO]);
	if (!cub->north)
		return (close_game(cub, "mlx_load_png NORTH failed", 1));
	cub->west = mlx_load_png(cub->path[WE]);
	if (!cub->west)
		return (close_game(cub, "mlx_load_png WEST failed", 1));
	cub->south = mlx_load_png(cub->path[SO]);
	if (!cub->south)
		return (close_game(cub, "mlx_load_png SOUTH failed", 1));
	return (0);
}

static void	ft_orientation(t_cub *cub)
{
	if (cub->dir == EA)
		cub->rotation_angle = EA * PI / 2;
	else if (cub->dir == SO)
		cub->rotation_angle = PI / 2;
	else if (cub->dir == WE)
		cub->rotation_angle = PI;
	else if (cub->dir == NO)
		cub->rotation_angle = 3 * PI / 2;
}

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	draw_map(cub);
	draw_4_rays(cub);
	draw_walls(cub, 0, 0);
	collision(cub);
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
	ft_orientation(cub);
	if (init_textures(cub))
		close_game(cub, "init_textures failed", 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	mlx_delete_image(cub->mlx, cub->img);
	mlx_terminate(cub->mlx);
	return (0);
}
