/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:56:36 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/22 21:59:49 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./../lib/libft/inc/libft.h"
# include "./../lib/libft/inc/ft_printf.h"
# include "./../lib/libft/inc/get_next_line.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

typedef struct s_cub	t_cub;
typedef enum e_dir		t_dir;

typedef enum e_dir
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3
}	t_dir;

typedef struct s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	void		*img_ptr;
	void		*mlx_ptr;
	void		*win_ptr;
	double		rotation_angle;
	t_list		*cub_info;
	int			gnl_free;
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
	int			player_x;
	int			player_y;
	int 		offset_x; // sombre
	int 		offset_y; // sombre
	int			move_bot;
	int			move_top;
	int			move_right;
	int			move_left;
}	t_cub;

void	init_cub(t_cub *cub);
int		parsing(int argc, char *map_file, t_cub *cub);
int		start_game(t_cub *cub);
void	ft_display(void *param);
void	ft_hook(void *param);
void	draw_tile(t_cub *cub, int x, int y, int color);
void	find_player_pos(t_cub *cub);
//SOMBRE !!!!!!!!

void ft_sombre(t_cub *cub);
void ft_sombre2(t_cub *cub);

//SOMBRE !!!!!!!!

# define MAUVE "\033[0;34m"
# define RED "\033[0;31m"
# define END "\033[m"

# define HEIGHT 1800
# define WIDTH 2400
# define FOV 60
# define MINI_LENGTH 500
# define TILE 60
# define PI 3.14159265
# define SPEED 6

#endif
