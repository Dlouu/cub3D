/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:35:18 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/08 16:22:04 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_text_and_hit(double *hit, mlx_texture_t **text, \
			double newhit, mlx_texture_t *newtexture)
{
	*text = newtexture;
	*hit = newhit;
}

static t_wall_orientation	get_orientation(t_cub *cub)
{
	if (is_horizontal_zero_intersection(cub) || (int)cub->ray_x % TILE != 0)
		return (HORIZONTAL);
	else
		return (VERTICAL);
}

static void	get_texture_for_ray(t_cub *c, \
	double *hit, mlx_texture_t **text)
{
	int	o;
	int	q;

	o = (c->tmp_angle >= PI / 2 && c->tmp_angle < 3 * PI / 2);
	q = get_quadrant_from_angle(c->tmp_angle);
	c->ray_x += o;
	if (get_orientation(c) == VERTICAL)
	{
		if (q == FIRST || q == FOURTH)
			assign_text_and_hit(hit, text, fmod(c->ray_y, TILE), c->east);
		else
			assign_text_and_hit(hit, text, fmod(c->ray_y, TILE), c->west);
	}
	else
	{
		if (q == FIRST || q == SECOND)
			assign_text_and_hit(hit, text, fmod(c->ray_x - o, TILE), c->south);
		else
			assign_text_and_hit(hit, text, fmod(c->ray_x - o, TILE), c->north);
	}
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
			offset_y = ((double)dist_to_top / \
				(cub->wall_bottom - cub->wall_top)) * texture->height;
			color = custom_texture_color(texture, x, (int)offset_y);
			mlx_put_pixel(cub->img, i, pixel_y, color);
		}
		else
			mlx_put_pixel(cub->img, i, pixel_y, get_color(cub->floor));
		pixel_y++;
	}
}

void	ft_draw_walls(t_cub *cub, int i, double wall_hit)
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
