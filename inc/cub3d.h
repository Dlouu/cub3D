/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:32:22 by niabraha          #+#    #+#             */
/*   Updated: 2025/03/10 16:23:51 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./../lib/libft/inc/libft.h"
# include "./../lib/libft/inc/ft_printf.h"
# include "./../lib/libft/inc/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

typedef struct s_cub			t_cub;
typedef enum e_dir				t_dir;
typedef enum e_quadrant			t_quadrant;
typedef enum e_wall_orientation	t_wall_orientation;

typedef enum e_dir
{
	EA = 0,
	NO = 1,
	WE = 2,
	SO = 3,
	FLOOR = 4,
	CEILING = 5,
}	t_dir;

typedef enum e_quadrant
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH
}	t_quadran;

typedef enum e_wall_orientation
{
	VERTICAL,
	HORIZONTAL
}	t_wall_orientation;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*east;
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*south;
	double			rotation_angle;
	t_list			*cub_info;
	int				gnl_free;
	int				player;
	int				fd;
	int				x;
	int				y;
	int				height;
	int				width;
	int				dir;
	char			*path[4];
	char			**map;
	int				floor[3];
	int				ceiling[3];
	int				offset_x;
	int				offset_y;
	int				move_bot;
	int				move_top;
	int				move_right;
	int				move_left;
	double			len_ray_left;
	double			len_ray_right;
	double			len_ray_top;
	double			len_ray_bot;
	double			ray_x;
	double			ray_y;
	double			tmp_angle;
	double			ray_distance;
	double			corrected_distance;
	double			wall_height;
	int				wall_top;
	int				wall_bottom;
}	t_cub;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

//parsing
void	init_cub(t_cub *cub);
int		parsing(int argc, char *map_file, t_cub *cub);
int		error_parsing(char *error);
void	extract_info_and_map(t_cub *cub, int i);
void	extract_color(char *line, int *color);
void	check_valid_char_map(t_cub *cub, char *line, int y);
void	map_validator(t_cub *cub);
void	flood_fill(t_cub *cub, char **map, t_coord pos);
void	replace_blanks_by_walls(char **map, int height, int width);

//game
int		start_game(t_cub *cub);
void	ft_display(void *param);
void	ft_hook(void *param);
void	collision(t_cub *cub);
void	draw_map(t_cub *cub);
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
int		get_key(char *line, int i);
int		get_color(int *colors);
bool	looking_for_zero(int height, char **map);

# define MAUVE "\033[0;34m"
# define RED "\033[0;31m"
# define END "\033[m"

# define HEIGHT 1200
# define WIDTH 1600
# define FOV 45
# define TILE 100
# define PI 3.14159265
# define SPEED 5
# define PROJ_PLANE 1931.370852 // (WIDTH / 2) / tan((FOV * (PI / 180)) / 2)

#endif
