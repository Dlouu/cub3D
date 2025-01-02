/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:14:31 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/02 11:03:40 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cub(t_cub *cub)
{
	cub->x = 0;
	cub->y = 0;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->floor[0] = -1;
	cub->floor[1] = -1;
	cub->floor[2] = -1;
	cub->ceiling[0] = -1;
	cub->ceiling[1] = -1;
	cub->ceiling[2] = -1;
	cub->map = NULL;
	cub->gnl_free = 0;
	cub->cub_info = NULL;
}

void	print_cub(t_cub *cub)
{
	t_list	*lst;

	lst = cub->cub_info;
	while (lst)
	{
		printf("%s\n", (char *)lst->data);
		lst = lst->next;
	}
	printf("\n---------------\nEXTRACTED INFO in struct :\n");
	if (cub->no)
		printf("NO: %s\n", cub->no);
	if (cub->so)
		printf("SO: %s\n", cub->so);
	if (cub->ea)
		printf("EA: %s\n", cub->ea);
	if (cub->we)
		printf("WE: %s\n", cub->we);
	if (cub->floor[0] != -1)
		printf("F: %d, %d, %d\n", cub->floor[0], cub->floor[1], cub->floor[2]);
	if (cub->ceiling[0] != -1)
		printf("C: %d, %d, %d\n", cub->ceiling[0], cub->ceiling[1], cub->ceiling[2]);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	cub.fd = open(argv[1], O_RDONLY);
	if (cub.fd == -1)
		return (printf("Error\n%sMap file not found\n%s", MAUVE, END), 0);
	init_cub(&cub);
	parsing(argc, argv[1], &cub);
	print_cub(&cub);
	start_game(&cub);
	// 	cub.mlx = mlx_init(cub.width, cub.height, "cub3D", true);
	// 	if (!(cub.mlx))
	// 		clean_close(ERROR_MLX, &cub, 1);
	// 	render_background(&cub);
	// 	render_player(&cub, -1, 1);
	// 	mlx_key_hook(cub.mlx, &keyhook, &cub);
	// 	mlx_loop(cub.mlx);
	// 	ft_printf(CROSS_EXIT);
	printf("Game ended\n");
	return (0);
	//return (clean_close(NULL, &cub, 0));
}
