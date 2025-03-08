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

Nils rayon 50 (regler le fisheye) //fait
Faire les textures
Gerer les positions // fait
mur avec un pixel de plus !
map force a etre carre et pas rectangle. le rayon s'arrete quand il rencontre un espace
*/

static void	ft_routine_rays(t_cub *cub, int i)
{
	double	start_x;
	double	start_y;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	while (1)
	{
		if (i == 50)
			cub->len_ray = sqrt(pow(cub->ray_x - start_x, 2) + \
				pow(cub->ray_y - start_y, 2));
		cub->ray_x += cos(cub->tmp_angle);
		cub->ray_y += sin(cub->tmp_angle);
		if (cub->map[(int)(cub->ray_y / TILE)][(int)(cub->ray_x / TILE)] == 32)
			break ;
		if (cub->map[(int)(cub->ray_y / TILE)][(int)(cub->ray_x / TILE)] == '1')
			break ;
	}
}

static void	ft_len_4_rays(t_cub *cub, double x, double y, int i)
{
	if (i == 0)
		cub->len_ray_top = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 1)
		cub->len_ray_right = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 2)
		cub->len_ray_bot = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
	else if (i == 3)
		cub->len_ray_left = sqrt(pow(cub->ray_x - x, 2) + \
			pow(cub->ray_y - y, 2));
}

static void	ft_draw_4_rays(t_cub *cub)
{
	double	start_x;
	double	start_y;
	int		i;
	int		x;
	int		y;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	i = -1;
	while (++i < 4)
	{
		cub->ray_x = start_x;
		cub->ray_y = start_y;
		while (1)
		{
			cub->ray_x += cos(cub->rotation_angle + PI / 2 * i);
			cub->ray_y += sin(cub->rotation_angle + PI / 2 * i);
			x = (int)(cub->ray_x / TILE);
			y = (int)(cub->ray_y / TILE);
			if (cub->map[y][x] == '1')
				break ;
		}
		ft_len_4_rays(cub, start_x, start_y, i);
	}
}

void	ft_draw_rays(t_cub *cub)
{
	double	start_x;
	double	start_y;
	int		i;

	start_x = cub->x * TILE + cub->offset_x + TILE / 2;
	start_y = cub->y * TILE + cub->offset_y + TILE / 2;
	ft_draw_4_rays(cub);
	i = 0;
	while (i++ < 100)
	{
		cub->tmp_angle = cub->rotation_angle - \
			(FOV * (PI / 180)) / 2 + (i * (FOV * (PI / 180)) / 100);
		cub->ray_x = start_x;
		cub->ray_y = start_y;
		ft_routine_rays(cub, i);
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
	ft_clear(cub);
	ft_draw_map(cub);
}

void	ft_display(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	ft_init_map(cub);
	ft_draw_rays(cub);
	ft_draw_walls(cub, 0);
	ft_collision(cub);
}



void	ft_draw_walls(t_cub *cub)
{
    int		col;
    double	ray_angle;
    double	ray_x;
    double	ray_y;
    double	start_x;
    double	start_y;
    double	ray_distance;
    double	corrected_distance;
    double	wall_height;
    int		wall_top;
    int		wall_bottom;
    double	distance_proj_plane;
    int		pixel_y;
    int		map_x;
    int		map_y;

    /* Calculate the distance to the projection plane.
       (WIDTH / 2) / tan(FOV/2) with FOV in radians */
    distance_proj_plane = (WIDTH / 2) / tan((FOV * (PI / 180)) / 2);

    /* Calculate the player's starting position: center of the current tile */
    start_x = cub->x * TILE + cub->offset_x + TILE / 2;
    start_y = cub->y * TILE + cub->offset_y + TILE / 2;

    /* Loop over every column of the window */
    for (col = 0; col < WIDTH; col++)
    {
        /* Calculate the current ray angle.
           Here, we scale the ray within the FOV across the window's width.
           The ray_angle varies from (rotation_angle - half FOV) on the left
           to (rotation_angle + half FOV) on the right. */
        ray_angle = cub->rotation_angle - ((FOV * (PI / 180)) / 2) +
                    (((double)col / (double)WIDTH) * (FOV * (PI / 180)));
        
        /* Initialize the ray's starting position */
        ray_x = start_x;
        ray_y = start_y;
        
        /* Cast the ray until a wall ('1') is hit. You might want to include bounds-checking too. */
        while (1)
        {
            ray_x += cos(ray_angle);
            ray_y += sin(ray_angle);
            
            /* Convert the ray's world coordinates into map indices */
            map_x = (int)(ray_x / TILE);
            map_y = (int)(ray_y / TILE);
            
            /* Check for a collision with a wall */
            if (cub->map[map_y][map_x] == '1')
                break ;
        }
        
        /* Compute the raw distance from the player to the wall hit */
        ray_distance = sqrt(pow(ray_x - start_x, 2) + pow(ray_y - start_y, 2));
        
        /* Correct for the fishbowl effect using the cosine of the angle difference */
        corrected_distance = ray_distance * cos(ray_angle - cub->rotation_angle);
        
        /* Calculate the projected wall height: (wall height / distance) * distance_to_projection_plane */
        wall_height = (TILE / corrected_distance) * distance_proj_plane;
        wall_top = (HEIGHT / 2) - (wall_height / 2);
        wall_bottom = (HEIGHT / 2) + (wall_height / 2);
        
        /* Draw the vertical stripe for this column:
           - Ceiling above wall_top
           - Wall between wall_top and wall_bottom
           - Floor below wall_bottom */
        for (pixel_y = 0; pixel_y < HEIGHT; pixel_y++)
        {
            if (pixel_y < wall_top)
                mlx_put_pixel(cub->img, col, pixel_y, 0xFFAAAAAA); /* Ceiling color */
            else if (pixel_y >= wall_top && pixel_y < wall_bottom)
                mlx_put_pixel(cub->img, col, pixel_y, 0xFF0000FF); /* Wall color */
            else
                mlx_put_pixel(cub->img, col, pixel_y, 0xFF333333); /* Floor color */
        }
    }
}