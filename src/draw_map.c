/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:03:55 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:30:57 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	apply_rotations(t_fdf *fdf, t_map_pt *pt, int *z)
{
	int	x;
	int	y;

	x = pt->x;
	y = pt->y * cos(fdf->x_rad) - *z * sin(fdf->x_rad);
	*z = pt->y * sin(fdf->x_rad) + *z * cos(fdf->x_rad);
	pt->x = x;
	pt->y = y;
	x = pt->x * cos(fdf->y_rad) + *z * sin(fdf->y_rad);
	y = pt->y;
	*z = -pt->x * sin(fdf->y_rad) + *z * cos(fdf->y_rad);
	pt->x = x;
	pt->y = y;
	x = pt->x * cos(fdf->z_rad) - pt->y * sin(fdf->z_rad);
	y = pt->x * sin(fdf->z_rad) + pt->y * cos(fdf->z_rad);
	pt->x = x;
	pt->y = y;
}

void	apply_perspective(t_fdf *fdf, t_map_pt *pt, int z)
{
	if (fdf->persp == 'I')
	{
		pt->x = 0.866 * pt->x - 0.5 * pt->y;
		pt->y = 0.866 * pt->y + 0.5 * pt->x - z;
	}
	else if (fdf->persp == 'C')
	{
		pt->x = (pt->x - 0.71 * z) - 0.71 * (pt->y - 0.71 * z);
		pt->y = (pt->y - 0.71 * z);
	}
	else
	{
		pt->x = pt->x;
		pt->y = pt->y;
	}
}

void	calc_pts_xy(t_fdf *fdf, t_map_pt *pt)
{
	int	z;

	pt->x = pt->col * fdf->zoom;
	pt->y = pt->row * fdf->zoom;
	z = (int)(pt->z * fdf->h_mod * fdf->zoom);
	apply_rotations(fdf, pt, &z);
	apply_perspective(fdf, pt, z);
}

void	connect_pts(t_fdf *fdf, t_map_pt *pt)
{
	int	row;
	int	col;

	row = pt->row;
	col = pt->col;
	if (pt->row != fdf->map->rows - 1)
		draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row + 1][col]);
	if (pt->col != fdf->map->cols - 1)
		draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row][col + 1]);
}

void	draw_map(t_fdf *fdf)
{
	get_img_size(fdf);
	mlx_resize_image(fdf->img, fdf->img_w, fdf->img_h);
	clean_img(fdf);
	fdf_map_iter(fdf, connect_pts);
	center_img(fdf);
}
