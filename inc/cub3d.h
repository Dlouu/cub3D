/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:56:36 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/16 22:04:39 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./../libft/inc/libft.h"
# include "./../libft/inc/ft_printf.h"
# include "./../libft/inc/get_next_line.h"
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_cub
{
	int		fd;
	int		x;
	int		y;
	int		dir;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	**map;
	int		floor[3];
	int		ceiling[3];
}	t_cub;

int	game_test(t_cub *cub);

# define MAUVE "\033[0;34m"
# define END "\033[m"

#endif
