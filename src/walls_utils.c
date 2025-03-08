/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/08 16:28:29 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	custom_texture_color(mlx_texture_t *image, int x, int y)
{
	uint8_t	*pixel;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel = &image->pixels[(y * image->width + x) * 4];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

bool	is_horizontal_zero_intersection(t_cub *cub)
{
	int	quadrant_offset;

	quadrant_offset = (cub->tmp_angle >= PI && cub->tmp_angle < 3 * PI / 2) || \
					(cub->tmp_angle >= 3 * PI / 2 && cub->tmp_angle < 2 * PI);
	return ((((int)cub->ray_x) % TILE == 0 && \
			((int)cub->ray_y + quadrant_offset) % TILE == 0) \
			&& (cub->map[(int)cub->ray_y / TILE] \
			[((int)cub->ray_x + quadrant_offset) / TILE] == '1' && \
			cub->map[(int)cub->ray_y / TILE][((int)cub->ray_x) / TILE] == '1' \
			&& (cub->map[((int)cub->ray_y + 1) / TILE] \
			[((int)cub->ray_x) / TILE] != '1' \
			|| cub->map[((int)cub->ray_y - 1) \
			/ TILE][((int)cub->ray_x) / TILE] != '1')));
}

t_quad	get_quadrant_from_angle(float angle)
{
	if (angle >= 0 && angle < PI / 2)
		return (FIRST);
	else if (angle >= PI / 2 && angle < PI)
		return (SECOND);
	else if (angle >= PI && angle < 3 * PI / 2)
		return (THIRD);
	else
		return (FOURTH);
}
