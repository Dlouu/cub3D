/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:35:18 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/21 18:35:58 by niabraha         ###   ########.fr       */
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

void	cast_ray(double angle, double start_x, double start_y, t_cub *cub)
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
