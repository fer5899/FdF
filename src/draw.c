/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 12:52:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/18 17:39:28 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

// void	set_pixel(t_map *map, int x, int y, int rgba)
// {
// 	if (0 <= x && x < map->cols && 0 <= y && y < map->rows)
// 	{
// 		map->img->pixels[y * 256 * 4 + x * 4 + 0] = get_r(rgba);
// 		map->img->pixels[y * 256 * 4 + x * 4 + 1] = get_g(rgba);
// 		map->img->pixels[y * 256 * 4 + x * 4 + 2] = get_b(rgba);
// 		map->img->pixels[y * 256 * 4 + x * 4 + 3] = get_a(rgba);
// 	}
// }

// void	draw_pt(t_map *map, t_map_pt *pt)
// {
// 	int	x;
// 	int	y;

// 	y = -3;
// 	x = -3;
// 	while (++x < 3)
// 	{
// 		while (++y < 3)
// 		{
// 			if (x == 0 && y == 0)
// 				set_pixel(map, x, y, get_rgba(pt->r, pt->g, pt->b, 255));
// 			else if (ft_abs(x) + ft_abs(y) == 1)
// 				set_pixel(map, x, y, get_rgba(pt->r, pt->g, pt->b, 200));
// 			else if (ft_abs(x) + ft_abs(y) == 2)
// 				set_pixel(map, x, y, get_rgba(pt->r, pt->g, pt->b, 100));
// 		}
// 	}
// }

// EL PARSER FALLA CON MAPAS GRANDES

// void	draw_line(mlx_image_t* img, t_map *map, t_map_pt *pt1, t_map_pt *pt2)
// {
	
// }

