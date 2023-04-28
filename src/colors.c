/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:32:40 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 11:19:38 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	set_colors_aux2(t_fdf *fdf, t_map_pt *pt)
{
	if (fdf->color == 1)
	{
		pt->r = 255;
		pt->g = 255;
		pt->b = 255;
	}
	if (fdf->color == 2)
	{
		pt->r = 0;
		pt->g = 0;
		pt->b = 0;
	}
	if (fdf->color == 9)
	{
		pt->r = 127;
		pt->g = 127;
		pt->b = 127;
	}
}

void	set_colors_aux(t_fdf *fdf, t_map_pt *pt)
{
	if (fdf->color == 6)
	{
		pt->r = 255;
		pt->g = 140;
		pt->b = 0;
	}
	if (fdf->color == 7)
	{
		pt->r = 0;
		pt->g = 255;
		pt->b = 140;
	}
	if (fdf->color == 8)
	{
		pt->r = 140;
		pt->g = 0;
		pt->b = 255;
	}
}

void	set_colors(t_fdf *fdf, t_map_pt *pt, t_map_pt *pt1, t_map_pt *pt2)
{
	if (fdf->color == 3)
	{
		pt->r = 255;
		pt->g = 0;
		pt->b = 0;
	}
	if (fdf->color == 4)
	{
		pt->r = 0;
		pt->g = 255;
		pt->b = 0;
	}
	if (fdf->color == 5)
	{
		pt->r = 0;
		pt->g = 0;
		pt->b = 255;
	}
	set_colors_aux(fdf, pt);
	set_colors_aux2(fdf, pt);
	pt1 = 0;
	pt2 = 0;
}
