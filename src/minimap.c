/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:38:07 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/22 12:18:26 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_inside_circle_minimap(t_cub *cub)
{
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	radius_squared;

	map_y = 0;
	radius_squared = 300 * 300;
	//ft_find_player_position(cub, &pos_x, &pos_y);
	pos_x = 300 - cub->player_x;
	pos_y = 300 - cub->player_y;
	while (cub->map[map_y])
	{
		map_x = 0;
		while (cub->map[map_y][map_x])
		{
			if (cub->map[map_y][map_x] == '1')
				draw_tile(cub, map_x * 20, map_y * 20);
			map_x++;
		}
		map_y++;
	}
}

void ft_edge_circle_minimap(t_cub *cub)
{
	int	x;
	int	y;
	int	r;
	int	x0;
	int	y0;
	int	i;

	r = 300;
	x0 = 300;
	y0 = 300;
	i = 0;
	while (i < 360)
	{
		x = r * cos(i * PI / 180);
		y = r * sin(i * PI / 180);
		mlx_put_pixel(cub->img, x0 + x, y0 + y, 0x00FF00FF);
		i++;
	}
}

void ft_minimap(t_cub *cub)
{
	ft_edge_circle_minimap(cub);
	ft_inside_circle_minimap(cub);
}
