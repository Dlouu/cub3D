/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:04:47 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/05 16:16:01 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	find_player_pos(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'E')
			{
				cub->player_x = x;
				cub->player_y = y;
				return ;
			}
			x++;
		}
		y++;
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
	find_player_pos(cub);
	ft_clear(cub);
	ft_draw_map(cub);
}
