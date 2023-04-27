/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:52:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 12:38:15 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	set_pixel(t_fdf *fdf, int x, int y, int rgba)
{
	int	pxl_idx;

	if (0 <= x && x < (int)fdf->img->width
		&& 0 <= y && y < (int)fdf->img->height)
	{
		pxl_idx = (y * fdf->img->width + x) * 4;
		fdf->img->pixels[pxl_idx] = get_r(rgba);
		fdf->img->pixels[pxl_idx + 1] = get_g(rgba);
		fdf->img->pixels[pxl_idx + 2] = get_b(rgba);
		fdf->img->pixels[pxl_idx + 3] = 255;
	}
}

void	draw_pt(t_fdf *fdf, t_map_pt *pt)
{
	int	x;
	int	y;
	int	calc;

	y = -fdf->brush;
	x = -fdf->brush;
	while (++x < fdf->brush)
	{
		while (++y < fdf->brush)
		{
			calc = (int) sqrt((double)(x * x + y * y));
			if (calc < fdf->brush)
				set_pixel(fdf, pt->x + x, pt->y + y,
					get_rgba(pt->r, pt->g, pt->b, 255));
		}
		y = -fdf->brush;
	}
}


void	draw_line(t_fdf *fdf, t_map_pt *pt1, t_map_pt *pt2)
{
	t_map_pt	pt;
	double		mx;
	double		my;
	int			n_pts;
	int			i;

	n_pts = ft_minmax(ft_abs(pt2->x - pt1->x), ft_abs(pt2->y - pt1->y), false);
	mx = (double)(pt2->x - pt1->x) / (double)(n_pts);
	my = (double)(pt2->y - pt1->y) / (double)(n_pts);
	i = 0;
	while (i <= n_pts)
	{
		pt.x = (int)(mx * i) + pt1->x;
		pt.y = (int)(my * i) + pt1->y;
		pt.r = ((int)((double)(pt2->r - pt1->r) / (double)(n_pts))) * (i + 1);
		pt.g = ((int)((double)(pt2->g - pt1->g) / (double)(n_pts))) * (i + 1);
		pt.b = ((int)((double)(pt2->b - pt1->b) / (double)(n_pts))) * (i + 1);
		if (fdf->style != 'g')
			set_colors(fdf, &pt, pt1, pt2);
		draw_pt(fdf, &pt);
		i++;
	}
}

