/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issplitable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:05:50 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/08/27 12:39:44 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_issplitable(int c)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}