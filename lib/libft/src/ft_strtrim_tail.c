/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_tail.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:05:48 by mbaumgar          #+#    #+#             */
/*   Updated: 2025/01/24 15:03:58 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strtrim_tail(char const *s1, char const *set, int critical)
{
	char	*str;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1, critical));
	len = ft_strlen(s1);
	while (ft_strrchr(set, s1[len]) && len > 0)
		len--;
	str = ft_substr(s1, 0, len + 1, critical);
	if (!str)
		return (NULL);
	return (str);
}
