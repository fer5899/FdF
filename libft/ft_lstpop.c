/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 16:06:11 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/02/17 12:07:00 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list *lst, t_list *to_pop)
{	
	if (lst == NULL || to_pop == NULL)
		return (NULL);
	while (lst != NULL)
	{
		if (lst->next == to_pop)
		{
			lst->next = lst->next->next;
			to_pop->next = NULL;
			return (to_pop);
		}
		lst = lst->next;
	}
	return (NULL);
}
