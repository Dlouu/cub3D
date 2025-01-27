/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/27 18:21:06 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_ray(t_cub *cub)
{
	double	ray_x;
	double	ray_y;
	double	start_x;
	double	start_y;
	double	tmp_angle;
	double	angle_step;
	double	start_angle;
	double	end_angle;
	int		x;
	int		y;
	int		i;

	angle_step = FOV / 100;
	start_angle = cub->rotation_angle - (FOV / 2);
	end_angle = cub->rotation_angle + (FOV / 2);
	tmp_angle = start_angle;
	i = 0;
	while (i++ < 100)
	{
		tmp_angle += angle_step;
		ray_x = cub->player_x * TILE + cub->offset_x + TILE / 2;
		ray_y = cub->player_y * TILE + cub->offset_y + TILE / 2;
		start_x = ray_x;
		start_y = ray_y;
		while (1)
		{
			ray_x += cos(tmp_angle);  // Fixed line
			ray_y += sin(tmp_angle);  // Fixed line
			x = (int)(ray_x / TILE);
			y = (int)(ray_y / TILE);
			if (x < 0 || y < 0 || x >= cub->width || y >= cub->height)
				break ;
			if (cub->map[y][x] == '1')
				break ;
			mlx_put_pixel(cub->img, (int)ray_x, (int)ray_y, 0x00FF00FF);
			cub->len_ray = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
			//printf("len\n: %f", cub->len_ray);
		}
	}
}

/* static void ft_collision(t_cub *cub)
{
	double left;
	double right;
	double top;
	double bot;

	left = (cub->player_x * TILE + cub->offset_x) - 1;
	right = (cub->player_x * TILE + cub->offset_x) + TILE;
	top = (cub->player_y * TILE + cub->offset_y) - 1;
	bot = (cub->player_y * TILE + cub->offset_y) + TILE;
	printf("pixels:   left: [%f]", left);
	printf("right: [%f]", right);
	printf("top: [%f]", top);
	printf("bot: [%f]\n\n", bot);
	int coord_left = (int)left / TILE;
	int coord_top = (int)top / TILE;
	int coord_right = (int)right / TILE;
	int coord_bot = (int)bot / TILE;

	printf("coord:     left[%d]", coord_left);
	printf("right[%d]", coord_right);
	printf("top[%d]", coord_top);
	printf("bot[%d]\n\n", coord_bot);
	printf("pos: %d   %d\n", cub->player_x, cub->player_y);
	cub->move_left = (coord_left > 0 && cub->map[coord_top][coord_left] != '1');
	cub->move_top = (coord_top > 0 && cub->map[coord_top][coord_left] != '1');
	cub->move_right = (coord_right < TILE && cub->map[coord_top][coord_right] != '1');
	cub->move_bot = (coord_bot < TILE && cub->map[coord_bot][coord_left] != '1');
} */

void	find_player_pos(t_cub *cub)
{
	int x;
	int	y;

	y = 0;
	while (cub->map[y])
	{
		x = 0;
		while (cub->map[y][x])
		{
			if (cub->map[y][x] == 'N')
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

static void draw_player(t_cub *cub)
{
	//find_player_pos(cub);
	draw_tile(cub, cub->player_x  * TILE + cub->offset_x, cub->player_y  * TILE + cub->offset_y, 0x0000FFFF);
}

void draw_tile(t_cub *cub, int x, int y, int color)
{
	int dx, dy;
	double local_x, local_y;

	dy = 0;
	while (dy < TILE)
	{
		dx = 0;
		while (dx < TILE)
		{
			local_x = x + dx;
			local_y = y + dy;
			mlx_put_pixel(cub->img, local_x, local_y, color);
			dx++;
		}
		dy++;
	}
}

static void	ft_test(t_cub *cub)
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
				draw_tile(cub, map_x * TILE, map_y * TILE, 0xFF0000FF);
			map_x++;
		}
		map_y++;
	}
	draw_player(cub);
}

static void ft_clear(t_cub *cub)
{
	int x;
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

void ft_display(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	find_player_pos(cub);
	ft_clear(cub);
	ft_test(cub);
	//ft_collision(cub);
	ft_draw_ray(cub);
}

void ft_hook(void *param)
{
	t_cub *cub;

	cub = (t_cub*)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(0);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) /* && cub->move_top */)
		cub->offset_y -= SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) /* && cub->move_bot */)
		cub->offset_y += SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) /* && cub->move_left */)
		cub->offset_x -= SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) /* && cub->move_right */)
		cub->offset_x += SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rotation_angle -= 0.05;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rotation_angle += 0.05;
	if (cub->rotation_angle < 0)
		cub->rotation_angle += 2 * PI;
	else if (cub->rotation_angle > 2 * PI)
		cub->rotation_angle -= 2 * PI;
	ft_test(cub);
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
