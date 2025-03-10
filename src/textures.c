/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/10 15:11:23 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_pixels(uint8_t *a, uint8_t *b)
{
	uint8_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	invert_texture(mlx_texture_t *texture)
{
	uint32_t	row;
	uint32_t	col;
	uint32_t	x;
	uint32_t	y;

	row = 0;
	while (row < texture->height)
	{
		col = 0;
		while (col < texture->width / 2)
		{
			x = (row * texture->width + col) * 4;
			y = (row * texture->width + (texture->width - 1 - col)) * 4;
			swap_pixels(&texture->pixels[x], &texture->pixels[y]);
			swap_pixels(&texture->pixels[x + 1], &texture->pixels[y + 1]);
			swap_pixels(&texture->pixels[x + 2], &texture->pixels[y + 2]);
			swap_pixels(&texture->pixels[x + 3], &texture->pixels[y + 3]);
			col++;
		}
		row++;
	}
}

int	init_textures(t_cub *cub)
{
	cub->east = mlx_load_png(cub->path[EA]);
	if (!cub->east)
		return (close_game(cub, "mlx_load_png EAST failed", 1));
	cub->north = mlx_load_png(cub->path[NO]);
	if (!cub->north)
		return (close_game(cub, "mlx_load_png NORTH failed", 1));
	cub->west = mlx_load_png(cub->path[WE]);
	if (!cub->west)
		return (close_game(cub, "mlx_load_png WEST failed", 1));
	cub->south = mlx_load_png(cub->path[SO]);
	if (!cub->south)
		return (close_game(cub, "mlx_load_png SOUTH failed", 1));
	invert_texture(cub->west);
	invert_texture(cub->south);
	return (0);
}
