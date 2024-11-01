/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/22 20:53:41 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_cub	cub;

	ft_printf("%sHello World%s\n", MAUVE, END);
	cub.fd = open("map.cub", O_RDONLY);
	cub.x = 0;
	cub.y = 0;
	cub.map = NULL;
	if (cub.fd == -1)
	{
		ft_printf("%sError\n%s", MAUVE, END);
		ft_printf("%s\n", strerror(errno));
	}
	return (0);
}