/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sombre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:27:35 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/22 11:16:10 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	x;
	int	y;
	int	color;
	int	tmp_x;
	int	tmp_y;
	int	r;
	int	x0;
	int	y0;
	int	dist_x; // distance x entre origine et le point
	int	dist_y; // distance y entre origine et le point
	int	scalar; // c'est pas un scalaire mais je me comprends #comprehensible
	float	rot_angle; // rotation angle
	float	rot_cos;
	float	rot_sin;

	x0 = 400; // Center of rotation
	y0 = 400;
	color = 0xFF0000FF;
	r = 300;
	x = 300; // Starting x coordinate of the square
	y = 300; // Starting y coordinate of the square
	rot_angle = cub->rotation_angle; // Get the rotation angle
	rot_cos = cos(rot_angle);
	rot_sin = sin(rot_angle);

	while (y < 1000)
	{
		tmp_y = y + cub->offset_y;
		while (x < 1400)
		{
			tmp_x = x + cub->offset_x;
			
			// Apply rotation transformation
			int rotated_x = x0 + (tmp_x - x0) * rot_cos - (tmp_y - y0) * rot_sin;
			int rotated_y = y0 + (tmp_x - x0) * rot_sin + (tmp_y - y0) * rot_cos;

			// Calculate scalar for color shading and radius check
			dist_x = rotated_x - x0;
			dist_y = rotated_y - y0;
			scalar = dist_x * dist_x + dist_y * dist_y;
			if (scalar < r * r)
				mlx_put_pixel(cub->img, rotated_x, rotated_y, color);
			x++;
			color -= 0x00000100;
		}
		x = 300; // Reset x coordinate for the next row
		y++;
	}
}
