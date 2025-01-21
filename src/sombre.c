/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sombre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:27:35 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/21 17:33:16 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
en gros ca c'est la minimap
*/
void	ft_sombre2(t_cub *cub)
{
	int	x;
	int	y;
	int	color;

	x = 600;
	y = 200;
	color = 0x0000FFFF;
	while (y < 1200)
	{
		while (x < 1200)
		{
			mlx_put_pixel(cub->img, x, y, color);
			x++;
			color += 0x00000100;
		}
		x = 600;
		y++;
	}
}

/*
gros cube qui represente la map entiere, trop gros pour rentrer dans la minimap
*/
void	ft_sombre(t_cub *cub)
{
	int	x;
	int	y;
	int	color;
	int	current_x;
	int	current_y;

	x = 300;
	y = 300;
	color = 0xFF0000FF;
	while (y < 1000)
	{
		current_y = y + cub->offset_y;
		while (x < 1400)
		{
			current_x = x + cub->offset_x;
			if (current_x >= cub->x_start && current_x < cub->x_end && \
				current_y >= cub->y_start && current_y < cub->y_end)
				mlx_put_pixel(cub->img, current_x, current_y, color);
			x++;
			color -= 0x00000100;
		}
		x = 300;
		y++;
	}
}
