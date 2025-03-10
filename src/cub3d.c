/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/10 11:22:35 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_game(t_cub *cub, char *error, int status)
{
	printf("%sError\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	if (cub->mlx)
	{
		mlx_delete_image(cub->mlx, cub->img);
		mlx_close_window(cub->mlx);
		mlx_terminate(cub->mlx);
	}
	wclear(1);
	exit(status);
}

int	error_parsing(char *error)
{
	printf("%sError\n%s", RED, END);
	printf("%s%s\n%s", MAUVE, error, END);
	wclear(1);
	exit(EXIT_FAILURE);
}

void	init_cub(t_cub *cub)
{
	cub->x = -1;
	cub->y = -1;
	cub->dir = -1;
	cub->floor[0] = -1;
	cub->floor[1] = -1;
	cub->floor[2] = -1;
	cub->ceiling[0] = -1;
	cub->ceiling[1] = -1;
	cub->ceiling[2] = -1;
	cub->height = -1;
	cub->width = -1;
}

int	main(int argc, char **argv)
{
	static t_cub	cub = {0};

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (printf("Error\n%sMap file not found\n%s", MAUVE, END), 0);
	init_cub(&cub);
	parsing(argc, argv[1], &cub);
	start_game(&cub);
	return (0);
}
