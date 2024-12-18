/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:34 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/18 16:19:19 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(int argc, char *map_file, t_cub *cub)
{
	if (argc != 2)
	{
		printf("%sError\n%s", MAUVE, END);
		printf("%sToo many arguments\n%s", MAUVE, END);
		printf("Usage: ./cub3d [map.cub]\n");
		return (0);
	}
	(void)cub;
	(void)map_file;
	// penser a limite la taille du jeu
	// exemple so long :
	// 	if (game.width > 110 || game.height > 55)
	// 		ft_error(ERROR_SIZE, &game);
	return (0);
}
