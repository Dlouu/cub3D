/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:22:44 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/27 17:34:33 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int	get_key(char *line, int i)
{
	char	*key;
	int		len;

	len = 0;
	while (line[i + len] && line[i + len] != ' ')
		len++;
	key = ft_strndup(line + i, len + 1, 0);
	if (!key)
		error_parsing("Malloc error in get_key");
	if (!ft_strcmp(key, "NO"))
		return (NO);
	else if (!ft_strcmp(key, "SO"))
		return (SO);
	else if (!ft_strcmp(key, "EA"))
		return (EA);
	else if (!ft_strcmp(key, "WE"))
		return (WE);
	else if (!ft_strcmp(key, "F"))
		return (FLOOR);
	else if (!ft_strcmp(key, "C"))
		return (CEILING);
	else
		return (-1);
}
