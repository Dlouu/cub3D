/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/14 15:46:53 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_color(int *colors)
{
    int red   = colors[0];
    int green = colors[1];
    int blue  = colors[2];

    return (red << 24) | (green << 16) | (blue << 8) | 0x000000FF;
}

static void	cast_ray(double angle, double start_x, double start_y, t_cub *cub)
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

static void	draw_column(t_cub *cub, int i, int wall_top, int wall_bottom)
{
	int	pixel_y;

	pixel_y = 0;
	printf("cub->c_color: %d\n", cub->c_color);
	printf("cub->f_color: %d\n", cub->f_color);
	while (pixel_y < HEIGHT)
	{
		if (pixel_y < wall_top)
			mlx_put_pixel(cub->img, i, pixel_y, get_color(cub->ceiling));
		else if (pixel_y < wall_bottom)
			mlx_put_pixel(cub->img, i, pixel_y, 0xFF0000FF);
		else
			mlx_put_pixel(cub->img, i, pixel_y, get_color(cub->floor));
		pixel_y++;
	}
}

void	ft_draw_walls(t_cub *cub)
{
	int		i;
	double	start_x;
	double	start_y;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	i = 0;
	while (i++ < WIDTH)
	{
		cub->tmp_angle = cub->rotation_angle - ((FOV * (PI / 180)) / 2)
			+ (((double)i / (double)WIDTH) * (FOV * (PI / 180)));
		cast_ray(cub->tmp_angle, start_x, start_y, cub);
		cub->ray_distance = sqrt(pow(cub->ray_x - start_x, 2) + \
			pow(cub->ray_y - start_y, 2));
		cub->corrected_distance = cub->ray_distance * \
			cos(cub->tmp_angle - cub->rotation_angle);
		cub->wall_height = (TILE / cub->corrected_distance) * PROJ_PLANE;
		cub->wall_top = (HEIGHT / 2) - (cub->wall_height / 2);
		cub->wall_bottom = (HEIGHT / 2) + (cub->wall_height / 2);
		draw_column(cub, i, cub->wall_top, cub->wall_bottom);
	}
}
