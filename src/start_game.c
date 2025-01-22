/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/22 18:13:07 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void ft_collision(t_cub *cub)
{
	int 	coord_x;
	int		coord_y;
	double	float_x;
	double	float_y;

	coord_x = ((cub->player_x * TILE) + cub->offset_x) / TILE;
	coord_y = ((cub->player_y * TILE) + cub->offset_y) / TILE;
	float_x = cub->player_x * TILE + (TILE / 2);
	float_y = cub->player_y * TILE + (TILE / 2);
	printf("joueur: [%d][%d]", coord_x, coord_y);
	printf("pixels: [%1.2f][%1.2f]", float_x, float_y);
	if (coord_x > 0 && cub->map[coord_y][coord_x - 1] == '1') // mur a gauche
		printf("gauche\n");
	if (coord_x < cub->width - 1 && cub->map[coord_y][coord_x + 1] == '1') // mur a droite
		printf("droite\n");
	if (coord_y < cub->height - 1 && cub->map[coord_y + 1][coord_x] == '1') // mur derriere
		printf("derriere\n");
	if (coord_y > 0 && cub->map[coord_y - 1][coord_x] == '1') // mur devant
		printf("devant\n");
}

void find_player_pos(t_cub *cub)
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
	printf("display\n");
	find_player_pos(cub);
	ft_clear(cub);
	ft_test(cub);
	ft_collision(cub);
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
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		cub->offset_y -= SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		cub->offset_y += SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		cub->offset_x -= SPEED;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		cub->offset_x += SPEED;
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
