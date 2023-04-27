/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:09:48 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:43:39 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	find_minmax(t_fdf *fdf, t_map_pt *pt)
{
	if (pt->x > fdf->map->max_x)
		fdf->map->max_x = pt->x;
	else if (pt->x < fdf->map->min_x)
		fdf->map->min_x = pt->x;
	else if (pt->y > fdf->map->max_y)
		fdf->map->max_y = pt->y;
	if (pt->y < fdf->map->min_y)
		fdf->map->min_y = pt->y;
	if (pt->z > fdf->map->max_z)
		fdf->map->max_z = pt->z;
	if (pt->z < fdf->map->min_z)
		fdf->map->min_z = pt->z;
}

void	normalize(t_fdf *fdf, t_map_pt *pt)
{
	pt->x += abs(fdf->map->min_x);
	pt->y += abs(fdf->map->min_y);
	if (pt->row == fdf->map->rows - 1 && pt->col == fdf->map->cols - 1)
	{
		fdf->map->max_x += abs(fdf->map->min_x);
		fdf->map->max_y += abs(fdf->map->min_y);
		fdf->map->min_x = 0;
		fdf->map->min_y = 0;
		fdf->img_w = fdf->map->max_x;
		fdf->img_h = fdf->map->max_y;
	}
}

void	get_img_size(t_fdf *fdf)
{
	fdf->map->max_x = 0;
	fdf->map->min_x = 0;
	fdf->map->max_y = 0;
	fdf->map->min_y = 0;
	fdf->map->max_z = 0;
	fdf->map->min_z = 0;
	fdf_map_iter(fdf, calc_pts_xy);
	fdf_map_iter(fdf, find_minmax);
	fdf_map_iter(fdf, normalize);
}
