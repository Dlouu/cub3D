/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/08 09:50:47 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdbool.h>

static unsigned int	custom_texture_color(mlx_texture_t *image, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel = &image->pixels[(y * image->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

typedef enum e_wall_orientation {
	VERTICAL,
	HORIZONTAL
}	t_wall_orientation;

bool	is_horizontal_zero_intersection(t_cub* cub) {
	int	quadrant_offset;

	quadrant_offset = (cub->tmp_angle >= PI && cub->tmp_angle < 3 * PI / 2) || \
					(cub->tmp_angle >= 3 * PI / 2 && cub->tmp_angle < 2 * PI);
	return ((((int)cub->ray_x) % TILE == 0 && \
			((int)cub->ray_y + quadrant_offset) % TILE == 0) \
			&& (cub->map[(int)cub->ray_y / TILE]\
			[((int)cub->ray_x + quadrant_offset) / TILE] == '1' &&\
			cub->map[(int)cub->ray_y / TILE][((int)cub->ray_x) / TILE] == '1' \
			&& (cub->map[((int)cub->ray_y + 1) / TILE]\
			[((int)cub->ray_x) / TILE] != '1' || cub->map[((int)cub->ray_y - 1)\
			/ TILE][((int)cub->ray_x) / TILE] != '1')));
}

static t_wall_orientation	get_orientation(t_cub *cub)
{
	if (is_horizontal_zero_intersection(cub) || (int)cub->ray_x % TILE != 0)
		return (HORIZONTAL);
	else
		return (VERTICAL);
}

void assign_text_and_hit(double *hit, mlx_texture_t **text, double newhit, mlx_texture_t *newtexture)
{
	*text = newtexture;
	*hit = newhit;
}

typedef enum e_quadrant {
	FIRST,
	SECOND,
	THIRD,
	FOURTH
}	t_quadrant;

t_quadrant get_quadrant_from_angle(float angle) {
	if (angle >= 0 && angle < PI / 2)
		return (FIRST);
	else if (angle >= PI / 2 && angle < PI)
		return (SECOND);
	else if (angle >= PI && angle < 3 * PI / 2)
		return (THIRD);
	else
		return (FOURTH);
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
		if (q == FIRST || q == FOURTH)
			assign_text_and_hit(hit, text, fmod(c->ray_y, TILE), c->east);
		else
			assign_text_and_hit(hit, text, fmod(c->ray_y, TILE), c->west);
	else
		if (q == FIRST || q == SECOND)
			assign_text_and_hit(hit, text, fmod(c->ray_x - o, TILE), c->south);
		else
			assign_text_and_hit(hit, text, fmod(c->ray_x - o, TILE), c->north);
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

void	ft_draw_walls(t_cub *cub)
{
	int				i;
	int				texture_x;
	double			start_x;
	double			start_y;
	double			wall_hit;
	mlx_texture_t	*texture;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	i = 0;
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
