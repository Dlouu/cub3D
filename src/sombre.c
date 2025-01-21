/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sombre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:27:35 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/21 18:07:59 by niabraha         ###   ########.fr       */
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
void	ft_sombre(t_cub *cub) //rouge
{
	int	x;
	int	y;
	int	color;
	int	current_x;
	int	current_y;
	int	r;
	int	x0;
	int	y0;
	int	dist_x; // distance x entre origine et le point
	int	dist_y; // distance y entre origine et le point
	int	scalar; // c'est pas un scalaire mais je me comprends #comprehensible

	x0 = 400;
	y0 = 400;
	color = 0xFF0000FF;
	r = 300;
	x = 300;
	y = 300;
	while (y < 1000)
	{
		current_y = y + cub->offset_y;
		while (x < 1400)
		{
			current_x = x + cub->offset_x;
			dist_x = current_x - x0;
			dist_y = current_y - y0;
			scalar = dist_x * dist_x + dist_y * dist_y;
			if (scalar < r * r)
				mlx_put_pixel(cub->img, current_x, current_y, color);
			x++;
			color -= 0x00000100;
		}
		x = 300; // MERCI CHATGPT DE MAVOIR DIT QUE JAVAIS OUBLIE DE RESET MA VALEUR #GrandRemplacement #PasCeluiQuOnPense
		y++;
	}
}
