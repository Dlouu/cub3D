/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/13 09:22:42 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_cub *cub, char *error, int status)
{
	if (error)
	{
		ft_printf("%sError\n%s", RED, END);
		ft_printf("%s%s\n%s", MAUVE, error, END);
	}
	if (cub->mlx)
	{
		if (cub->img)
			mlx_delete_image(cub->mlx, cub->img);
		if (cub->north)
			mlx_delete_texture(cub->north);
		if (cub->east)
			mlx_delete_texture(cub->east);
		if (cub->south)
			mlx_delete_texture(cub->south);
		if (cub->west)
			mlx_delete_texture(cub->west);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	if (cub->fd != -1)
		close(cub->fd);
	wclear(1);
	exit(status);
}

static void	ft_orientation(t_cub *cub)
{
	if (cub->dir == NO)
		cub->rotation_angle = 3 * PI / 2;
	else if (cub->dir == EA)
		cub->rotation_angle = EA * PI / 2;
	else if (cub->dir == SO)
		cub->rotation_angle = PI / 2;
	else if (cub->dir == WE)
		cub->rotation_angle = PI;
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

void	start_game(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		close_game(cub, "mlx_init failed", 1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		close_game(cub, "mlx_new_image failed", 1);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		close_game(cub, "mlx_image_to_window failed", 1);
	ft_orientation(cub);
	if (init_textures(cub))
		close_game(cub, "init_textures failed", 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
}
