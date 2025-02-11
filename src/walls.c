/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/11 15:57:11 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_ray(t_cub *cub, double angle, double *distance)
{
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	int		hit;

	ray_x = cub->x * TILE + cub->offset_x + TILE / 2;
	ray_y = cub->y * TILE + cub->offset_y + TILE / 2;
	hit = 0;
	while (!hit)
	{
		ray_x += cos(angle) * 0.1;
		ray_y += sin(angle) * 0.1;
		map_x = (int)(ray_x / TILE);
		map_y = (int)(ray_y / TILE);
		if (map_x >= cub->width || map_y >= cub->height || map_x < 0
			|| map_y < 0)
			break ;
		if (cub->map[map_y][map_x] == '1')
			hit = 1;
	}
	*distance = sqrt(pow(ray_x - (cub->x * TILE + cub->offset_x + \
		TILE / 2), 2) + pow(ray_y - (cub->y * TILE + \
			cub->offset_y + TILE / 2), 2));
}

void	calculate_wall_height(double distance, int *wall_height)
{
	*wall_height = (TILE * HEIGHT) / distance;
	if (*wall_height > HEIGHT)
		*wall_height = HEIGHT;
}

void	draw_wall_column(t_cub *cub, int screen_x, int wall_height)
{
	int	y_start;
	int	y_end;

	y_start = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	while (y_start < y_end)
	{
		mlx_put_pixel(cub->img, screen_x, y_start, 0x000044FF);
		y_start++;
	}
}

void	ft_draw_walls(t_cub *cub)
{
	double	angle_increment;
	double	angle;
	double	distance;
	int		screen_x;
	int		wall_height;

	angle_increment = FOV * (PI / 180) / WIDTH;
	screen_x = 0;
	while (screen_x < WIDTH)
	{
		angle = cub->rotation_angle - (FOV * (PI / 180)) / 2 + \
			(screen_x * angle_increment);
		cast_ray(cub, angle, &distance);
		calculate_wall_height(distance, &wall_height);
		draw_wall_column(cub, screen_x, wall_height);
		screen_x++;
	}
}
