/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 13:18:17 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:53:19 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	free_pt(t_fdf *fdf, t_map_pt *pt)
{
	fdf = 0;
	free(pt);
}

void	free_map(t_fdf *fdf)
{
	int	row;

	fdf_map_iter(fdf, free_pt);
	row = -1;
	while (++row < fdf->map->rows)
	{
		free(fdf->map->pts[row]);
	}
	free(fdf->map->pts);
	free(fdf->map);
}

void	leaks(void)
{
	system("leaks -q fdf");
}
