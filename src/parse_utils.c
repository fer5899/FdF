/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 11:51:39 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:23:10 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	iter_to_lower(unsigned int i, char *str)
{
	if (i > 0)
		*str = ft_tolower(*str);
}

int	get_row_len(t_map_pt **pt)
{
	int	count;

	count = 0;
	while (*pt)
	{
		count++;
		*pt += 1;
		if ((*pt)->x == -1)
			break ;
	}
	return (count);
}

int	get_arr_len(char **arr)
{
	int	count;

	count = 0;
	while (*arr)
	{
		count++;
		arr++;
	}
	return (count);
}

void	free_split(char	***strtab)
{
	int	i;

	i = 0;
	while ((*strtab)[i] != NULL)
	{
		free((*strtab)[i]);
		i++;
	}
	free(*strtab);
}
