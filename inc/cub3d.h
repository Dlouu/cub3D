/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:56:36 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/08 15:59:50 by mbaumgar         ###   ########.fr       */
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
	mlx_t	*mlx;
	t_list	*cub_info;
	int		gnl_free;
	int		fd;
	int		x;
	int		y;
	int		height;
	int		width;
	int		dir;
	char	*path[4];
	char	**map;
	int		floor[3];
	int		ceiling[3];
}	t_cub;

void	init_cub(t_cub *cub);
int		parsing(int argc, char *map_file, t_cub *cub);
int		start_game(t_cub *cub);

# define MAUVE "\033[0;34m"
# define END "\033[m"

#endif
