/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:04:26 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/08 16:47:46 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	*ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		wfree(result[i]);
		i++;
	}
	wfree(result);
	return (NULL);
}

char	**ft_lstsplit(t_list *lst, int critical)
{
	char	**tab;
	int		i;
	t_list	*temp_lst;

	i = 0;
	if (!lst)
		return (NULL);
	temp_lst = lst;
	tab = (char **)walloc(sizeof(char *) * (ft_lstsize(lst) + 1), critical);
	if (!tab)
		return (NULL);
	while (temp_lst != NULL)
	{
		tab[i] = ft_strdup(temp_lst->data, critical);
		if (!tab[i])
			return (ft_free(tab));
		i++;
		temp_lst = temp_lst->next;
	}
	tab[i] = NULL;
	ft_lstclear(&lst, wfree);
	return (tab);
}
