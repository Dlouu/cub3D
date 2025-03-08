/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:04:47 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/08 15:44:19 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_init_textures(t_cub *cub)
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
	cub->east_texture = mlx_texture_to_image(cub->mlx, cub->east);
	if (!cub->east_texture)
		return (close_game(cub, "mlx_texture_to_image EAST failed", 1));
	cub->north_texture = mlx_texture_to_image(cub->mlx, cub->north);
	if (!cub->north_texture)
		return (close_game(cub, "mlx_texture_to_image NORTH failed", 1));
	cub->west_texture = mlx_texture_to_image(cub->mlx, cub->west);
	if (!cub->west_texture)
		return (close_game(cub, "mlx_texture_to_image WEST failed", 1));
	cub->south_texture = mlx_texture_to_image(cub->mlx, cub->south);
	if (!cub->south_texture)
		return (close_game(cub, "mlx_texture_to_image SOUTH failed", 1));
	return (0);
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

static void	ft_draw_map(t_cub *cub)
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

static void	ft_clear(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(cub->img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	ft_init_map(t_cub *cub)
{
	ft_clear(cub);
	ft_draw_map(cub);
}
