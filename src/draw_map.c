/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:03:55 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 12:25:31 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	calc_pts_xy(t_fdf *fdf)
{
	int	row;
	int	col;
	int	z;
	t_map_pt	*pt;

	row = -1;
	col = -1;
	while (++row < fdf->map->rows)
	{
		while (++col < fdf->map->cols)
		{
			pt = fdf->map->pts[row][col];
			// apply min distance and zoom
			pt->x = col * fdf->zoom;
			pt->y = row * fdf->zoom;
			z = (int)(pt->z * fdf->h_mod * fdf->zoom);
			
			// pt->x += fdf->map->x_offset;
			// pt->y += fdf->map->y_offset;
			// apply perspective transformation
			pt->x = 0.866 * pt->x - 0.5 * pt->y;
			pt->y = 0.866 * pt->y + 0.5 * pt->x - z;
		}
		col = -1;
	}
		// apply rotation transformation
}

void	draw_map(t_fdf *fdf, int brush_size)
{
	int	row;
	int	col;

	row = -1;
	col = -1;
	// calculate x y positions of all points
	calc_pts_xy(fdf);
	// iterate through all the points
	while (++row < fdf->map->rows)
	{
		while (++col < fdf->map->cols)
		{
			// for each point, if it isn't in the last row or column
				// draw a line from the current point to the point with row+1
			if (row != fdf->map->rows - 1)
				draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row+1][col], brush_size);
				// draw a line from the current point to the point with col+1
			if (col != fdf->map->cols - 1)
				draw_line(fdf, fdf->map->pts[row][col], fdf->map->pts[row][col+1], brush_size);
		}
		col = -1;
	}
}

// && fdf->map->pts[row][col]->z <= 
