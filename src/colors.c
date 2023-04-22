/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:32:40 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/22 20:27:19 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"


void	set_colors(t_fdf *fdf, t_map_pt *pt, t_map_pt *pt1, t_map_pt *pt2)
{
	if (fdf->style == 'o')
	{
		pt->r = 255;
		pt->g = 140;
		pt->b = 0;
	}
	pt1 = 0;
	pt2 = 0;
	// else if (fdf->color == 'h') Add Earth and other colors
	// {
		
	// }
}
