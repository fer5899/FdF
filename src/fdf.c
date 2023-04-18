/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/18 18:57:52 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define	WIDTH 256
#define HEIGHT 256
// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// // Print the window width and height.
// static void ft_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("button pressed: %d | action: %d | modifier: %d\n", button, action, mods);
// 	printf("height: %d | width: %d \n\n", mlx->height, mlx->width);
// }

int	main(int argc, char **argv)
{
	t_fdf	*fdf;
	// mlx_image_t	*img;
	// int		i = -1;
	// t_map_pt *pt;
	// int		col = -1;

	if (argc != 2)
		return (ft_printf_fd(
				"Introduzca únicamente un archivo .fdf como argumento\n", 2), 1);
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
		return (ft_printf_fd(
				"Introduzca un archivo .fdf como argumento\n", 2), 1);
	if (open(argv[1], O_RDONLY) == -1)
		return (ft_printf_fd(
				"Error al abrir el archivo\n", 2), 1);
	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, false);
	fdf = (t_fdf *) ft_calloc(1, sizeof(t_fdf));
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!fdf->mlx)
		ft_error();

	/* Do stuff */
	parse_map(argv[1], fdf);
	if (!fdf->map)
		ft_error();

	// img = mlx_new_image(mlx, 256, 100); //map->cols, map->rows
	// if (!(img))
	// 	return (free(map), 0);
	// i = -1;
	// while (++i < 256*100*4) // map->rows*map->cols
	// {
	// 	if (i % 4 == 3)
	// 		img->pixels[i] = 255;
	// }
	// (*(map->img))->pixels[0] = 255;
	// mlx_image_to_window(mlx, *(map->img), 0, 0);

	// draw_pt(map, init_pt(7, 9, 12, 0xFF00FFFF));
	// SEGMENTATION FAULT DONDE?

	// // Register a hook and pass mlx as an optional param.
	// // NOTE: Do this before calling mlx_loop!
	// mlx_mouse_hook(mlx, ft_hook, mlx);
	ft_printf("no peta");
	mlx_loop(fdf->mlx);
	mlx_terminate(fdf->mlx);
	
	// // ft_printf("width = %d, height = %d\n", map->cols, map->rows);
	// while (++row < map->rows)
	// {
	// 	while (++col < map->cols)
	// 	{
	// 		pt = map->pts[row][col];
	// 		ft_printf("(%d,%d)(%d,%d,%d) ", pt->x, pt->y, pt->r, pt->g, pt->b);
	// 	}
	// 	ft_printf("\n", row);
	// 	col = -1;
	// }
	return (EXIT_SUCCESS);
}
