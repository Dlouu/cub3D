/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/05 16:25:30 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_walls(t_cub *cub) //ni plus ni moins que l'aide de Xi Jinping
{
	double	ray_x, ray_y, angle, distance, corrected_distance;
	double	start_x, start_y;
	double	angle_increment;
	int		screen_x, wall_height;
	int		map_x, map_y;
	int		hit;

	start_x = cub->player_x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->player_y * TILE + cub->offset_y + TILE / 2;
	angle_increment = (FOV * (PI / 180)) / WIDTH;
	for (screen_x = 0; screen_x < WIDTH; screen_x++)
	{
		angle = cub->rotation_angle - (FOV * (PI / 180)) / 2 + (screen_x * angle_increment);
		ray_x = start_x;
		ray_y = start_y;
		hit = 0;
		while (!hit)
		{
			ray_x += cos(angle);
			ray_y += sin(angle);
			map_x = (int)(ray_x / TILE);
			map_y = (int)(ray_y / TILE);
			if (cub->map[map_y][map_x] == '1')
				hit = 1;
		}
		distance = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		corrected_distance = distance * cos(angle - cub->rotation_angle);
		wall_height = (TILE * HEIGHT) / corrected_distance;
		if (wall_height > HEIGHT)
			wall_height = HEIGHT;
		int	y_start = (HEIGHT / 2) - (wall_height / 2);
		int	y_end = (HEIGHT / 2) + (wall_height / 2);
		for (int y = y_start; y < y_end; y++)
			mlx_put_pixel(cub->img, screen_x, y, 0x04044FF);
	}
}

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	ft_init_map(cub);
	ft_draw_rays(cub);
	ft_draw_walls(cub);
	ft_collision(cub);
}

int	start_game(t_cub *cub)
{
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", 0);
	if (!cub->mlx)
		return (printf("marche pas init\n"), 1);
	cub->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img)
		return (printf("marche pas img\n"), 1);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) == -1)
		return (printf("marche pas img to win\n"), 1);
	mlx_loop_hook(cub->mlx, ft_display, cub);
	mlx_loop_hook(cub->mlx, ft_hook, cub);
	mlx_loop(cub->mlx);
	return (0);
}
