E //
tmp_angle: 0.513127
cub->rotation_angle: 0.000000

N //
tmp_angle: 5.225516
cub->rotation_angle: 4.712389

version qui lag pas
/* void	ft_draw_walls(t_cub *cub) //ni plus ni moins que l'aide de Xi Jinping
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
} */

/*
Dlou gere messages d'erreurs de tout
creer des textures ahah
Determiner taille max pour virer les connards
inverser NO SO EA WE pour que ca colle a la logique
verifier si les newline a la fin c'est comme il faut

Nils rayon 50 (regler le fisheye)
Faire les textures
Gerer les positions
mur avec un pixel de plus !
*/