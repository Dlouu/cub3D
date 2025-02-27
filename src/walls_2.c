/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:35:18 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/24 14:46:48 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void invert_west_and_south_textures(mlx_texture_t *texture)
{
	unsigned int row_size;
	unsigned int row;
	unsigned int col;
	int			comp;
	int 		tmp;

	row = -1;
	row_size = texture->width * 4;
	while (++row < texture->height)
	{
		col = -1;
		while (++col < texture->width * 0.5)
		{
			comp = -1;
			while (++comp < 4)
			{
				tmp = texture->pixels[(row * row_size + col * 4) + comp];
				texture->pixels[row * row_size + col * 4 + comp] = texture->pixels[(row * row_size + (texture->width - col - 1) * 4) + comp];
				texture->pixels[(row * row_size + (texture->width - col - 1) * 4) + comp] = tmp;
			}
		}
	}
}

int	ft_init_textures(t_cub *cub)
{
	printf("ft_init_textures\n");
	cub->east = mlx_load_png(cub->path[EA]);
	if (!cub->east)
		return (close_game(cub, "mlx_load_png EAST failed", 1));
	cub->north = mlx_load_png(cub->path[NO]);
	if (!cub->north)
		return (close_game(cub, "mlx_load_png NORTH failed", 1));
	cub->south = mlx_load_png(cub->path[SO]);
	if (!cub->south)
		return (close_game(cub, "mlx_load_png SOUTH failed", 1));
	cub->west = mlx_load_png(cub->path[WE]);
	if (!cub->west)
		return (close_game(cub, "mlx_load_png WEST failed", 1));
	printf("texture->east->width = %d\n", cub->east->width);
	printf("texture->west->width = %d\n", cub->west->width);
	invert_west_and_south_textures(cub->west);
	printf("texture->east->width = %d\n", cub->east->width);
	printf("texture->west->width = %d\n", cub->west->width);
	invert_west_and_south_textures(cub->south);
	printf("texture->east->width = %d\n", cub->east->width);
	printf("texture->west->width = %d\n", cub->west->width);
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
