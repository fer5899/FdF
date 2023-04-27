/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:03:55 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 18:00:20 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	clean_img(t_fdf *fdf)
{
	int i;

	i = -1;
	while (++i < (int)(fdf->img->height * fdf->img->width * 4))
		fdf->img->pixels[i] = 0;
}

void	center_img(t_fdf *fdf)
{
	fdf->img->instances[0].x = (WIDTH - fdf->img_w) / 2;
	fdf->img->instances[0].y = (HEIGHT - fdf->img_h) / 2;
}

void	calc_pts_xy(t_fdf *fdf, t_map_pt *pt)
{
	int	z;

	pt->x = pt->col * fdf->zoom;
	pt->y = pt->row * fdf->zoom;
	z = (int)(pt->z * fdf->h_mod * fdf->zoom);
	// apply rotation transformation
	// apply perspective transformation
	pt->x = 0.866 * pt->x - 0.5 * pt->y;
	pt->y = 0.866 * pt->y + 0.5 * pt->x - z;
}

void	connect_pts(t_fdf *fdf, t_map_pt *pt)
{
	int	row;
	int	col;

	row = pt->row;
	col = pt->col;
	if (pt->row != fdf->map->rows - 1)
		draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row+1][col]);
	if (pt->col != fdf->map->cols - 1)
		draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row][col+1]);
}

void	draw_map(t_fdf *fdf)
{
	get_img_size(fdf);
	mlx_resize_image(fdf->img, fdf->img_w, fdf->img_h);
	fdf_map_iter(fdf, connect_pts);
}

// && fdf->map->pts[row][col]->z <= 
