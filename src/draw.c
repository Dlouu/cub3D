/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:35:18 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/12 16:24:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static uint32_t	custom_texture_color(mlx_texture_t *image, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel = &image->pixels[(y * image->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	draw_textured_column(t_cub *cub, int i, \
			mlx_texture_t *texture, int x)
{
	int				pixel_y;
	int				dist_to_top;
	unsigned int	color;
	double			offset_y;

	pixel_y = 0;
	while (pixel_y < HEIGHT - 1)
	{
		if (pixel_y < 0 || pixel_y >= HEIGHT || i < 0 || i >= WIDTH)
			return ;
		if (pixel_y < cub->wall_top)
			mlx_put_pixel(cub->img, i, pixel_y, get_color(cub->ceiling));
		else if (pixel_y <= cub->wall_bottom)
		{
			dist_to_top = pixel_y - cub->wall_top;
			offset_y = ((double)dist_to_top \
				/ (cub->wall_bottom - cub->wall_top)) * texture->height;
			color = custom_texture_color(texture, x, (int)offset_y);
			mlx_put_pixel(cub->img, i, pixel_y, color);
		}
		else
			mlx_put_pixel(cub->img, i, pixel_y, get_color(cub->floor));
		pixel_y++;
	}
}

void	draw_walls(t_cub *cub, int i, double wall_hit)
{
	int				texture_x;
	double			start_x;
	double			start_y;
	mlx_texture_t	*texture;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	while (i++ < WIDTH)
	{
		cub->tmp_angle = cub->rotation_angle - ((FOV * (PI / 180)) / 2)
			+ (((double)i / (double)WIDTH) * (FOV * (PI / 180)));
		if (cub->tmp_angle > 2 * PI)
			cub->tmp_angle = cub->tmp_angle - 2 * PI;
		cast_ray(cub->tmp_angle, start_x, start_y, cub);
		cub->ray_distance = sqrt(pow(cub->ray_x - start_x, 2) \
			+ pow(cub->ray_y - start_y, 2));
		cub->corrected_distance = cub->ray_distance \
			* cos(cub->tmp_angle - cub->rotation_angle);
		cub->wall_height = (TILE / cub->corrected_distance) * PROJ_PLANE;
		cub->wall_top = (HEIGHT / 2) - (cub->wall_height / 2);
		cub->wall_bottom = (HEIGHT / 2) + (cub->wall_height / 2);
		get_texture_for_ray(cub, &wall_hit, &texture);
		texture_x = (int)((wall_hit / TILE) * texture->width);
		draw_textured_column(cub, i, texture, texture_x);
	}
}

static void	draw_tile(int x, int y)
{
	int		dx;
	int		dy;
	double	local_x;
	double	local_y;

	dy = 0;
	while (dy < TILE)
	{
		dx = 0;
		while (dx < TILE)
		{
			local_x = x + dx;
			local_y = y + dy;
			dx++;
		}
		dy++;
	}
}

void	draw_map(t_cub *cub)
{
	int		map_x;
	int		map_y;

	map_y = 0;
	while (cub->map[map_y])
	{
		map_x = 0;
		while (cub->map[map_y][map_x])
		{
			if (cub->map[map_y][map_x] == '1')
				draw_tile(map_x * TILE, map_y * TILE);
			map_x++;
		}
		map_y++;
	}
}
