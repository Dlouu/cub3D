/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:02:08 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/10 11:18:28 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(double angle, double start_x, double start_y, t_cub *cub)
{
	int	map_x;
	int	map_y;

	cub->ray_x = start_x;
	cub->ray_y = start_y;
	while (1)
	{
		cub->ray_x += cos(angle);
		cub->ray_y += sin(angle);
		map_x = (int)(cub->ray_x / TILE);
		map_y = (int)(cub->ray_y / TILE);
		if (cub->map[map_y][map_x] == '1')
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

void	draw_4_rays(t_cub *cub)
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
