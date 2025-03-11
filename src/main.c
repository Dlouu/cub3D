/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/03/11 13:06:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	static t_cub	cub = {.floor[0] = -1, .ceiling[0] = -1};

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (error_parsing("Map file not found"));
	parsing(argc, argv[1], &cub);
	start_game(&cub);
	close_game(&cub, NULL, 0);
	return (0);
}
