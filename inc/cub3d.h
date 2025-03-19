/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:32:22 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/19 13:01:47 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./../lib/libft/inc/libft.h"
# include "./../lib/libft/inc/ft_printf.h"
# include "./../lib/libft/inc/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_cub			t_cub;
typedef enum e_dir				t_dir;
typedef enum e_quadrant			t_quadrant;
typedef enum e_wall_orientation	t_wall_orientation;

typedef enum e_dir
{
	NO = 0,
	EA = 1,
	SO = 2,
	WE = 3,
	FLOOR = 4,
	CEILING = 5,
}	t_dir;

typedef enum e_quadrant
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH
}	t_quadrant;

typedef enum e_wall_orientation
{
	VERTICAL,
	HORIZONTAL
}	t_wall_orientation;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	t_list			*cub_info;
	char			**map;
	char			*path[4];
	int				floor[3];
	int				ceiling[3];
	int				player;
	int				fd;
	int				x;
	int				y;
	int				height;
	int				width;
	int				dir;
	int				offset_x;
	int				offset_y;
	int				move_bot;
	int				move_top;
	int				move_right;
	int				move_left;
	int				wall_top;
	int				wall_bottom;
	double			wall_height;
	double			len_ray_left;
	double			len_ray_right;
	double			len_ray_top;
	double			len_ray_bot;
	double			ray_x;
	double			ray_y;
	double			tmp_angle;
	double			rotation_angle;
	double			ray_distance;
	double			corrected_distance;
}	t_cub;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

//parsing
void	parsing(int argc, char *map_file, t_cub *cub);
void	extractor(t_cub *cub, int i);
void	extract_color(char *line, int *color);
void	validator(t_cub *cub);
void	flood_fill(t_cub *cub, char **map, t_coord pos);
int		error_parsing(char *error);

//game
void	start_game(t_cub *cub);
void	ft_display(void *param);
void	ft_hook(void *param);
void	collision(t_cub *cub);
int		close_game(t_cub *cub, char *error, int status);

//rays
void	draw_4_rays(t_cub *cub);
void	cast_ray(double angle, double x, double y, t_cub *cub);

//walls
int		init_textures(t_cub *cub);
void	get_texture_for_ray(t_cub *c, double *hit, mlx_texture_t **text);
void	draw_walls(t_cub *cub, int i, double wall_hit);

//utils
int		skip_blank(char *line);
int		get_color(int *colors);
int		get_key(char *line, int i);
int		get_map_size(t_cub *cub, t_list *lst);
void	get_player_position(t_cub *cub, char *str, int y);
bool	looking_for_zero(int height, char **map);

//colors
# define MAUVE "\033[0;34m"
# define RED "\033[0;31m"
# define END "\033[m"

# define HEIGHT 1200
# define WIDTH 1600
# define FOV 45
# define TILE 100
# define PI 3.14159265359
# define SPEED 10
# define PROJ_PLANE 1931.370852

/*
	PROJ_PLANE :
	(WIDTH / 2) / tan((FOV * (PI / 180)) / 2
	= 1931.370852
*/

#endif
