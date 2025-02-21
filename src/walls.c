/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/21 18:35:13 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	custom_texture_color(mlx_image_t *image, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel = &image->pixels[(y * image->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

static void	get_texture_for_ray(t_cub *cub, double *hit, mlx_image_t **texture)
{
	if (fabs(cos(cub->tmp_angle)) > fabs(sin(cub->tmp_angle)))
	{
		if (cos(cub->tmp_angle) > 0)
			*texture = cub->east_texture;
		else
			*texture = cub->west_texture;
		*hit = fmod(cub->ray_y, TILE);
	}
	else
	{
		if (sin(cub->tmp_angle) > 0)
			*texture = cub->south_texture;
		else
			*texture = cub->north_texture;
		*hit = fmod(cub->ray_x, TILE);
	}
}

static void	draw_textured_column(t_cub *cub, int i, mlx_image_t *texture, int x)
{
	int				pixel_y;
	int				dist_to_top;
	unsigned int	color;
	double			offset_y;

	pixel_y = 0;
	while (pixel_y < HEIGHT)
	{
		if (pixel_y < 0 || pixel_y >= HEIGHT || i < 0 || i >= WIDTH)
			return ;
		if (pixel_y < cub->wall_top)
			mlx_put_pixel(cub->img, i, pixel_y, cub->c_color);
		else if (pixel_y <= cub->wall_bottom)
		{
			dist_to_top = pixel_y - cub->wall_top;
			offset_y = ((double)dist_to_top / \
				(cub->wall_bottom - cub->wall_top)) * texture->height;
			color = custom_texture_color(texture, x, (int)offset_y);
			mlx_put_pixel(cub->img, i, pixel_y, 0x00FFFFFF);
		}
		else
			mlx_put_pixel(cub->img, i, pixel_y, cub->f_color);
		pixel_y++;
	}
}

void	ft_draw_walls(t_cub *cub)
{
	int			i;
	int			texture_x;
	double		start_x;
	double		start_y;
	double		wall_hit;
	mlx_image_t	*texture;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	i = 0;
	while (i++ < WIDTH)
	{
		cub->tmp_angle = cub->rotation_angle - ((FOV * (PI / 180)) / 2)
			+ (((double)i / (double)WIDTH) * (FOV * (PI / 180)));
		cast_ray(cub->tmp_angle, start_x, start_y, cub);
		cub->ray_distance = sqrt(pow(cub->ray_x - start_x, 2) \
			+ pow(cub->ray_y - start_y, 2));
		cub->corrected_distance = cub->ray_distance * \
			cos(cub->tmp_angle - cub->rotation_angle);
		cub->wall_height = (TILE / cub->corrected_distance) * PROJ_PLANE;
		cub->wall_top = (HEIGHT / 2) - (cub->wall_height / 2);
		cub->wall_bottom = (HEIGHT / 2) + (cub->wall_height / 2);
		get_texture_for_ray(cub, &wall_hit, &texture);
		texture_x = (int)((wall_hit / TILE) * texture->width);
		draw_textured_column(cub, i, texture, texture_x);
	}
}
