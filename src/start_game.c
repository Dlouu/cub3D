/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/13 18:51:19 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 0xFF00FFFF = rose
 0x00F0FFF0 = cyan
 0x00FF00FF = vert
 0x00FFFF00 = jaune
*/

static void	ft_inside_circle_minimap(t_cub *cub)
{
	int		x, y;
	double	rotated_x, rotated_y;
	double	cx, cy, local_x, local_y;
	int		dx, dy;
	int		map_x, map_y;

	cx = 300; // Center of the minimap
	cy = 300;

	map_y = 0;
	while (cub->map[map_y]) // Ensure cub->map[map_y] is not NULL
	{
		map_x = 0;
		while (cub->map[map_y][map_x]) // Ensure cub->map[map_y][map_x] is not out of bounds
		{
			if (cub->map[map_y][map_x] == '1')
			{
				x = map_x * 20;
				y = map_y * 20;

				dy = 0;
				while (dy < 20)
				{
					dx = 0;
					while (dx < 20)
					{
						local_x = x + dx - cx;
						local_y = y + dy - cy;
						rotated_x = local_x * cos(cub->rotation_angle) - local_y * sin(cub->rotation_angle) + cx;
						rotated_y = local_x * sin(cub->rotation_angle) + local_y * cos(cub->rotation_angle) + cy;
						if (rotated_x >= 0 && rotated_x < 600 && rotated_y >= 0 && rotated_y < 600)
							mlx_put_pixel(cub->img, (int)rotated_x, (int)rotated_y, 0x00FF00FF);
						dx++;
					}
					dy++;
				}
			}
			map_x++;
		}
		map_y++;
	}
}


static void ft_edge_circle_minimap(t_cub *cub)
{
    int x;
    int y;
    int r;
    int x0;
    int y0;
    int i;

    r = 300;
    x0 = 300;
    y0 = 300;
    i = 0;
    while (i < 360)
    {
        x = r * cos(i * PI / 180);
        y = r * sin(i * PI / 180);
        mlx_put_pixel(cub->img, x0 + x, y0 + y, 0x00FF00FF);
        i++;
    }
}

static void ft_minimap(t_cub *cub)
{
    ft_edge_circle_minimap(cub);
    ft_inside_circle_minimap(cub);
}


static void ft_display(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	ft_minimap(cub);
}

static void ft_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		//ft-transparent
		cub->rotation_angle += 0.05;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rotation_angle -= 0.05;
	if (cub->rotation_angle > 2 * PI)
		cub->rotation_angle -= 2 * PI;
	if (cub->rotation_angle < 0)
		cub->rotation_angle += 2 * PI;
}

int	start_game(t_cub *cub)
{
	
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		return (printf("marche pas init\n"), 1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (printf("marche pas img\n"), 1);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) ==-1)
		return (printf("marche pas img to win\n"), 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
