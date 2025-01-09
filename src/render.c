/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niabraha <niabraha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:13:28 by niabraha          #+#    #+#             */
/*   Updated: 2025/01/09 17:17:42 by niabraha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void run_mlx(t_cub *cub)
{
	if (argc == 2)
	{
		cub->fd = open(argv[1], O_RDONLY);
		if (cub->fd == -1)
		{
			ft_printf("%sError\n%s", MAUVE, END);
			ft_printf("%s\n", strerror(errno));
		}
	}
	else
	{
		ft_printf("%sError\n%s", MAUVE, END);
		ft_printf("%s\n", strerror(errno));
	}
}