/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:26:19 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/06 14:38:18 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_cub *cub)
{
	cub->img_east = mlx_load_png("img/east.png");
	if (!cub->img_east)
	{
		printf("marche pas img_east\n");
		exit(1);
	}
	cub->img_west = mlx_load_png("img/west.png");
	if (!cub->img_west)
	{
		printf("marche pas img_west\n");
		exit(1);
	}
	cub->img_north = mlx_load_png("img/north.png");
	if (!cub->img_north)
	{
		printf("marche pas img_north\n");
		exit(1);
	}
	cub->img_south = mlx_load_png("img/south.png");
	if (!cub->img_south)
	{
		printf("marche pas img_south\n");
		exit(1);
	}	
}

void	cast_ray(t_cub *cub, double angle, double *distance, int *is_vertical)
{
    double	ray_x;
    double	ray_y;
    int		map_x;
    int		map_y;
    int		hit;

    ray_x = cub->player_x * TILE + cub->offset_x + TILE / 2;
    ray_y = cub->player_y * TILE + cub->offset_y + TILE / 2;
    hit = 0;
    *is_vertical = 0;
    while (!hit)
    {
        ray_x += cos(angle) * 0.1;
        ray_y += sin(angle) * 0.1;
        map_x = (int)(ray_x / TILE);
        map_y = (int)(ray_y / TILE);
        if (map_x >= cub->width || map_y >= cub->height || map_x < 0 || map_y < 0)
            break ;
        if (cub->map[map_y][map_x] == '1')
        {
            hit = 1;
            if (fmod(ray_x, TILE) < 0.1 || fmod(ray_x, TILE) > TILE - 0.1)
                *is_vertical = 1;
            else
                *is_vertical = 0;
        }
    }
    *distance = sqrt(pow(ray_x - (cub->player_x * TILE + cub->offset_x + \
        TILE / 2), 2) + pow(ray_y - (cub->player_y * TILE + \
            cub->offset_y + TILE / 2), 2));
}


void	calculate_wall_height(double distance, int *wall_height)
{
	*wall_height = (TILE * HEIGHT) / distance;
	if (*wall_height > HEIGHT)
		*wall_height = HEIGHT;
}

void	draw_wall_column(t_cub *cub, int screen_x, int wall_height, int is_vertical, double angle)
{
    int		y_start;
    int		y_end;
    int		tex_x;
    int		tex_y;
    float	step;
    float	tex_pos;
    int		color;
    mlx_texture_t *tex;

    // Choose the texture based on the wall orientation and ray angle
    if (is_vertical)
    {
        if (cos(angle) > 0)
            tex = cub->img_east; // Ray is facing east
        else
            tex = cub->img_west; // Ray is facing west
    }
    else
    {
        if (sin(angle) > 0)
            tex = cub->img_south; // Ray is facing south
        else
            tex = cub->img_north; // Ray is facing north
    }

    y_start = (HEIGHT / 2) - (wall_height / 2);
    y_end = (HEIGHT / 2) + (wall_height / 2);
    step = (float)tex->height / (float)wall_height;
    tex_pos = (y_start < 0 ? -y_start * step : 0);

    // Calculate texture X coordinate
    tex_x = (int)(fmod(cub->ray_x, TILE) / TILE * tex->width);
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= tex->width)
        tex_x = tex->width - 1;

    while (y_start < y_end)
    {
        if (y_start >= 0 && y_start < HEIGHT)
        {
            tex_y = (int)tex_pos & (tex->height - 1);
            tex_pos += step;

            // Get color from texture
            color = *(int *)(tex->pixels + (tex_y * tex->width + tex_x) * 4);

            // Put pixel on screen
            mlx_put_pixel(cub->img, screen_x, y_start, color);
        }
        y_start++;
    }
}


void	ft_draw_walls(t_cub *cub)
{
    double	angle_increment;
    double	angle;
    double	distance;
    int		screen_x;
    int		wall_height;
    int		is_vertical;

    angle_increment = FOV * (PI / 180) / WIDTH;
    screen_x = 0;
    while (screen_x < WIDTH)
    {
        angle = cub->rotation_angle - (FOV * (PI / 180)) / 2 + \
            (screen_x * angle_increment);
        cast_ray(cub, angle, &distance, &is_vertical);
        calculate_wall_height(distance, &wall_height);
        draw_wall_column(cub, screen_x, wall_height, is_vertical, angle);
        screen_x++;
    }
}

