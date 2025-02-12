/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:32:22 by niabraha          #+#    #+#             */
/*   Updated: 2025/02/12 13:32:24 by niabraha         ###   ########.fr       */
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

typedef struct s_cub	t_cub;
typedef enum e_dir		t_dir;

typedef enum e_dir
{
	EA = 0,
	NO = 1,
	WE = 2,
	SO = 3,
	FLOOR = 4,
	CEILING = 5,
}	t_dir;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*texture;
	void		*img_ptr;
	void		*mlx_ptr;
	void		*win_ptr;
	double		rotation_angle;
	t_list		*cub_info;
	int			gnl_free;
	int			player;
	int			fd;
	int			x;
	int			y;
	int			height;
	int			width;
	int			dir;
	char		*path[4];
	char		**map;
	int			floor[3];
	int			ceiling[3];
	int			f_color;
	int			c_color;
	int			offset_x;
	int			offset_y;
	int			move_bot;
	int			move_top;
	int			move_right;
	int			move_left;
	double		len_ray;
	double		len_ray_left;
	double		len_ray_right;
	double		len_ray_top;
	double		len_ray_bot;
	double		ray_x;
	double		ray_y;
	double		tmp_angle;
	mlx_image_t	*img_east;
	mlx_image_t	*img_west;
	mlx_image_t	*img_north;
	mlx_image_t	*img_south;
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

//a delete, pour test
void	print_map(t_cub *cub, char **map);

//game
int		start_game(t_cub *cub);
void	ft_display(void *param);
void	ft_hook(void *param);
void	ft_collision(t_cub *cub);

// rays
void	ft_draw_rays(t_cub *cub);

//init_map
void	ft_init_map(t_cub *cub);

//walls

void	cast_ray(t_cub *cub, double angle, double *distance);
void	calculate_wall_height(double distance, int *wall_height);
void	draw_wall_column(t_cub *cub, int screen_x, int wall_height);
void	ft_draw_walls(t_cub *cub);

//utils
int		skip_blank(char *line);
int		get_key(char *line, int i);
bool	looking_for_zero(int height, char **map);
int		get_rgba(int r, int g, int b);

# define MAUVE "\033[0;34m"
# define RED "\033[0;31m"
# define END "\033[m"

# define HEIGHT 1200
# define WIDTH 1600
# define FOV 45
# define MINI_LENGTH 500
# define TILE 100
# define PI 3.14159265
# define SPEED 5

#endif
