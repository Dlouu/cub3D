/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/12/05 10:57:43 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->map = NULL;
	cub->x = 0;
	cub->y = 0;
}

int	main(void)
{
	t_cub	cub;

	ft_printf("%sHello World%s\n", MAUVE, END);
	cub.fd = open("map.cub", O_RDONLY);
	init_cub(&cub);
	if (cub.fd == -1)
	{
		ft_printf("%sError\n%s", MAUVE, END);
		ft_printf("%s\n", strerror(errno));
	}
	return (0);
}