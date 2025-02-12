/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:02:08 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/12 13:32:35 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_routine_rays(t_cub *cub)
{
	double	start_x;
	double	start_y;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	while (1)
	{
		cub->ray_x += cos(cub->tmp_angle);
		cub->ray_y += sin(cub->tmp_angle);
		if (cub->map[(int)(cub->ray_y / TILE)][(int)(cub->ray_x / TILE)] == '1')
			break ;
	}
}

static void	ft_len_4_rays(t_cub *cub, double x, double y, int i)
{
	if (i == 0)
		cub->len_ray_top = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 1)
		cub->len_ray_right = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 2)
		cub->len_ray_bot = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 3)
		cub->len_ray_left = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
}

static void	ft_draw_4_rays(t_cub *cub)
{
	double	start_x;
	double	start_y;
	int		i;
	int		x;
	int		y;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	i = -1;
	while (++i < 4)
	{
		cub->ray_x = start_x;
		cub->ray_y = start_y;
		while (1)
		{
			cub->ray_x += cos(cub->rotation_angle + PI / 2 * i);
			cub->ray_y += sin(cub->rotation_angle + PI / 2 * i);
			x = (int)(cub->ray_x / TILE);
			y = (int)(cub->ray_y / TILE);
			if (cub->map[y][x] == '1')
				break ;
		}
		ft_len_4_rays(cub, start_x, start_y, i);
	}
}

void	ft_draw_rays(t_cub *cub)
{
	double	start_x;
	double	start_y;
	int		i;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	ft_draw_4_rays(cub);
	i = 0;
	while (i++ < 100)
	{
		cub->tmp_angle = cub->rotation_angle - \
			(FOV * (PI / 180)) / 2 + (i * (FOV * (PI / 180)) / 100);
		cub->ray_x = start_x;
		cub->ray_y = start_y;
		ft_routine_rays(cub);
	}
}
