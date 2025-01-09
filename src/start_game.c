/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:50:41 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/09 17:55:17 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static mlx_image_t* image;

static void ft_display_minimap(void *param)
{
/* 	(void) param;
	mlx_t	*mlx;
	int		i;
	double	angle;
	double	x_minimap;
	double	y_minimap;

	i = 0;
	// cub = NULL;
	mlx = NULL;
	while (i < 360)
	{
		angle = i;
		x_minimap = 50 * cos(angle * PI / 180);
		y_minimap = 50 * sin(angle * PI / 180);
		mlx_put_pixel(image, 70 + x_minimap, 70 + y_minimap, 0x00FF00);
		i++;
	}*/
	(void) param;
} 

static void ft_display(void *param)
{
	ft_display_minimap(param);
}

int	start_game(t_cub *cub)
{
	mlx_t* mlx;
	(void)cub;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, ft_display, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
