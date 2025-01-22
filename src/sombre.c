/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sombre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:27:35 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/22 12:20:05 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_tile(t_cub *cub, int x, int y)
{
	int dx, dy;
	double local_x, local_y;

	dy = 0;
	while (dy < 20)
	{
		dx = 0;
		while (dx < 20)
		{
			local_x = x + dx + cub->offset_x;
			local_y = y + dy + cub->offset_y;
			mlx_put_pixel(cub->img, 300 + local_x, 300 + local_y, 0x00FF00FF);
			dx++;
		}
		dy++;
	}
}

/*
en gros ca c'est la minimap
*/
void	ft_sombre2(t_cub *cub) // bleu
{
	int	x;
	int	y;
	int	r;
	int	x0;
	int	y0;
	int	i;
	int	color;

	r = 300;
	x0 = 400;
	y0 = 400;
	i = 0;
	color = 0x0000FFFF;
	while (i < 360)
	{
		x = r * cos(i * PI / 180);
		y = r * sin(i * PI / 180);
		mlx_put_pixel(cub->img, x0 + x, y0 + y, color);
		i++;
	}
}

/*
gros cube qui represente la map entiere, trop gros pour rentrer dans la minimap
*/
void	ft_sombre(t_cub *cub) // rouge
{
	int		map_x;
	int		map_y;

	map_y = 0;
	//ft_find_player_position(cub, &pos_x, &pos_y);
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
