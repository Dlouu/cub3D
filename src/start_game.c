/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/21 13:49:53 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 0xFF00FFFF = rose
 0x00F0FFF0 = cyan
 0x00FF00FF = vert
 0x00FFFF00 = jaune
*/

void rotate_pixel(double local_x, double local_y, double cx, double cy, double rotation_angle, double *rotated_x, double *rotated_y)
{
	*rotated_x = local_x * cos(rotation_angle) - local_y * sin(rotation_angle) + cx;
	*rotated_y = local_x * sin(rotation_angle) + local_y * cos(rotation_angle) + cy;
}


int is_inside_circle(double rotated_x, double rotated_y, double cx, double cy, double radius_squared)
{
		double dist_squared; 
		
		dist_squared = (rotated_x - cx) * (rotated_x - cx) + (rotated_y - cy) * (rotated_y - cy);
		return (dist_squared <= radius_squared);
}

//en haut bien

static void ft_clear(t_cub *cub)
{
	int x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(cub->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void ft_display(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	ft_clear(cub);
	ft_minimap(cub);
}

void ft_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rotation_angle += 0.05;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rotation_angle -= 0.05;
	if (cub->rotation_angle > 2 * PI)
		cub->rotation_angle -= 2 * PI;
	if (cub->rotation_angle < 0)
		cub->rotation_angle += 2 * PI;
}

int	start_game(t_cub *cub)
{
	
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		return (printf("marche pas init\n"), 1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (printf("marche pas img\n"), 1);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) ==-1)
		return (printf("marche pas img to win\n"), 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
