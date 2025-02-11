/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:05 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/02/11 14:21:05 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	go_to_next_comma(char *line, int i)
{
	while (line[i] && line[i] != ',')
		i++;
	return (i);
}

int	is_valid_color_format(char *line)
{
	int		i;
	int		comma;

	comma = 0;
	i = 1;
	i += skip_blank(line + i);
	while (line[i])
	{
		if (line[i] == ',')
		{
			if (line[i + 1] == ',' || line[i + 1] == '\0')
				return (error_parsing("Invalid color (missing number)"));
			if (i != 0 && line[i - 1] == ' ')
				return (error_parsing("Invalid color (missing number)"));
			comma++;
		}
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (error_parsing("Invalid color format"));
		i++;
	}
	if (comma != 2)
		return (error_parsing("Invalid color format (comma error)"));
	return (1);
}

void	extract_color(char *line, int *color)
{
	int	i;

	i = 1;
	if (!is_valid_color_format(line))
		return ;
	if (color[0] != -1)
		printf("%sError, color already set\n%s", RED, END);
	color[0] = ft_atoi(line + i + 1);
	i = go_to_next_comma(line, i);
	color[1] = ft_atoi(line + i + 1);
	i = go_to_next_comma(line, i + 1);
	color[2] = ft_atoi(line + i + 1);
	if (color[0] < 0 || color[1] < 0 || color[2] < 0)
		error_parsing("Invalid color value (no negative allowed)");
	if (color[0] > 255 || color[1] > 255 || color[2] > 255)
		error_parsing("Invalid color value (255 max range)");
}
