/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/30 11:35:40 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_draw_4_rays(t_cub *cub)
{
	double	ray_x;
	double	ray_y;
	double	start_x;
	double	start_y;
	double	angle;
	int		i;
	int		x;
	int		y;

	start_x = cub->player_x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->player_y * TILE + cub->offset_y + TILE / 2;
	i = 0;
	angle = cub->rotation_angle;
	while (i++ < 4)
	{
		ray_x = start_x;
		ray_y = start_y;
		while (1)
		{
			ray_x += cos(angle);
			ray_y += sin(angle);
			x = (int)(ray_x / TILE);
			y = (int)(ray_y / TILE);
			if (cub->map[y][x] == '1')
				break;
			mlx_put_pixel(cub->img, (int)ray_x, (int)ray_y, 0x0000FFFF);
		}
		if (i == 0)
			cub->len_ray_top = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		else if (i == 1)
			cub->len_ray_right = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		else if (i == 2)
			cub->len_ray_bot = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		else if (i == 3)
			cub->len_ray_left = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		cub->rotation_angle += PI / 2;
	}
}

void	ft_draw_ray(t_cub *cub)
{
	double	ray_x;
	double	ray_y;
	double	start_x;
	double	start_y;
	double	tmp_angle;
	double	angle_increment;
	int		x;
	int		y;
	int		i;

	start_x = cub->player_x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->player_y * TILE + cub->offset_y + TILE / 2;
	angle_increment = (FOV * (PI / 180)) / 100;
	ft_draw_4_rays(cub);
	i = 0;
	while (i < 100)
	{
		tmp_angle = cub->rotation_angle - (FOV * (PI / 180)) / 2 + (i * angle_increment);
		printf("tmp_angle: %f\n", tmp_angle);
		ray_x = start_x;
		ray_y = start_y;
		while (1)
		{
			ray_x += cos(tmp_angle);
			ray_y += sin(tmp_angle);
			x = (int)(ray_x / TILE);
			y = (int)(ray_y / TILE);
			if (cub->map[y][x] == '1')
				break ;
			mlx_put_pixel(cub->img, (int)ray_x, (int)ray_y, 0x00FF00FF);
			if (i == 51)
				cub->len_ray = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
		}
		i++;
	}
}

static void	ft_collision(t_cub *cub)
{
	if (cub->len_ray_right < 20)
		cub->move_right = 0;
	else
		cub->move_right = 1;
	if (cub->len_ray_left < 20)
		cub->move_left = 0;
	else
		cub->move_left = 1;
	if (cub->len_ray_top < 20)
		cub->move_top = 0;
	else
		cub->move_top = 1;
	if (cub->len_ray_bot < 20)
		cub->move_bot = 0;
	else
		cub->move_bot = 1;
}

void	find_player_pos(t_cub *cub)
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
			else if (cub->map[y][x] == 'W')
			{
				cub->player_x = x;
				cub->player_y = y;
				cub->rotation_angle = PI;
				return ;
			}
			else if (cub->map[y][x] == 'N')
			{
				cub->player_x = x;
				cub->player_y = y;
				cub->rotation_angle = 3 * PI / 2;
				return ;
			}
			else if (cub->map[y][x] == 'S')
			{
				cub->player_x = x;
				cub->player_y = y;
				cub->rotation_angle = PI / 2;
				return ;
			}
			
			x++;
		}
		y++;
	}
}

static void	draw_player(t_cub *cub)
{
	//find_player_pos(cub);
	draw_tile(cub, cub->player_x, cub->player_y, 0x0000FFFF);
}

void	draw_tile(t_cub *cub, int x, int y, int color)
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
			mlx_put_pixel(cub->img, local_x, local_y, color);
			dx++;
		}
		dy++;
	}
}

void	ft_draw_map(t_cub *cub)
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

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	find_player_pos(cub);
	ft_clear(cub);
	ft_draw_map(cub);
	ft_draw_ray(cub); // rayons verts
	ft_draw_4_rays(cub); // rayons bleus
	ft_collision(cub); // en gros je calcule les longueurs des rayons bleus et si trop proche d'un mur je bloque le mouvement
}

void ft_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(cub->mlx);
		exit(0);
	}

	// Calculate the movement direction based on the player's rotation angle
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W) && cub->move_top)
	{
		cub->offset_x += cos(cub->rotation_angle) * SPEED;
		cub->offset_y += sin(cub->rotation_angle) * SPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S) && cub->move_bot)
	{
		cub->offset_x -= cos(cub->rotation_angle) * SPEED;
		cub->offset_y -= sin(cub->rotation_angle) * SPEED;
	}

	// Strafe left and right (A and D keys)
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A) && cub->move_left)
	{
		cub->offset_x += cos(cub->rotation_angle - PI / 2) * SPEED;
		cub->offset_y += sin(cub->rotation_angle - PI / 2) * SPEED;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D) && cub->move_right)
	{
		cub->offset_x += cos(cub->rotation_angle + PI / 2) * SPEED;
		cub->offset_y += sin(cub->rotation_angle + PI / 2) * SPEED;
	}

	// Rotate left and right (arrow keys)
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		cub->rotation_angle -= 0.05;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		cub->rotation_angle += 0.05;

	// Normalize the rotation angle to stay within 0 to 2*PI
	if (cub->rotation_angle < 0)
		cub->rotation_angle += 2 * PI;
	else if (cub->rotation_angle > 2 * PI)
		cub->rotation_angle -= 2 * PI;

	// Redraw the map to reflect the changes
	ft_draw_map(cub);
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
