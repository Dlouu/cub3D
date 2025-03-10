/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/10 12:28:39 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static t_quadran	get_quadrant_from_angle(float angle)
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

static bool	is_horizontal_zero_intersection(t_cub *cub)
{
	int	quadrant_offset;

	quadrant_offset = get_quadrant_from_angle(cub->tmp_angle) == THIRD \
					|| get_quadrant_from_angle(cub->tmp_angle) == FOURTH;
	return ((((int)cub->ray_x) % TILE == 0 \
			&& ((int)cub->ray_y + quadrant_offset) % TILE == 0) \
			&& (cub->map[(int)cub->ray_y / TILE] \
			[((int)cub->ray_x + quadrant_offset) / TILE] == '1' \
			&& cub->map[(int)cub->ray_y / TILE] \
			[((int)cub->ray_x) / TILE] == '1' \
			&& (cub->map[((int)cub->ray_y + 1) / TILE] \
			[((int)cub->ray_x) / TILE] != '1' \
			|| cub->map[((int)cub->ray_y - 1) / TILE] \
			[((int)cub->ray_x) / TILE] != '1')));
}

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

void	get_texture_for_ray(t_cub *c, \
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
