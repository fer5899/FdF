/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:20:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 13:25:02 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	fdf_map_iter(t_fdf *fdf, void (*f)(t_fdf *, t_map_pt *))
{
	int			row;
	int			col;
	t_map_pt	*pt;

	row = -1;
	col = -1;
	while (++row < fdf->map->rows)
	{
		while (++col < fdf->map->cols)
		{
			pt = fdf->map->pts[row][col];
			f(fdf, pt);
		}
		col = -1;
	}
}
