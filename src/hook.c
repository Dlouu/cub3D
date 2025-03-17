/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:17:03 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/17 12:31:37 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collision(t_cub *cub)
{
	if (cub->len_ray_right < 50)
		cub->move_right = 0;
	else
		cub->move_right = 1;
	if (cub->len_ray_left < 50)
		cub->move_left = 0;
	else
		cub->move_left = 1;
	if (cub->len_ray_top < 50)
		cub->move_top = 0;
	else
		cub->move_top = 1;
	if (cub->len_ray_bot < 50)
		cub->move_bot = 0;
	else
		cub->move_bot = 1;
}

static void	move_forward_backward(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && cub->move_top)
	{
		cub->offset_x += cos(cub->rotation_angle) * SPEED;
		cub->offset_y += sin(cub->rotation_angle) * SPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) && cub->move_bot)
	{
		cub->offset_x -= cos(cub->rotation_angle) * SPEED;
		cub->offset_y -= sin(cub->rotation_angle) * SPEED;
	}
}

static void	move_left_right(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) && cub->move_left)
	{
		cub->offset_x += cos(cub->rotation_angle - PI / 2) * SPEED;
		cub->offset_y += sin(cub->rotation_angle - PI / 2) * SPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) && cub->move_right)
	{
		cub->offset_x += cos(cub->rotation_angle + PI / 2) * SPEED;
		cub->offset_y += sin(cub->rotation_angle + PI / 2) * SPEED;
	}
}

static void	rotate(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rotation_angle -= 0.05;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rotation_angle += 0.05;
	if (cub->rotation_angle < 0)
		cub->rotation_angle += 2 * PI;
	else if (cub->rotation_angle > 2 * PI)
		cub->rotation_angle -= 2 * PI;
}

void	ft_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		close_game(cub, NULL, 0);
	move_forward_backward(cub);
	move_left_right(cub);
	rotate(cub);
}
