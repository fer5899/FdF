/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 17:02:39 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void ft_error(void)
{
	ft_printf_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	clean_img(t_fdf *fdf)
{
	int i;

	i = -1;
	while (++i < (int)(fdf->img->height * fdf->img->width * 4))
	{
		fdf->img->pixels[i] = 255;
		if (i % 4 == 3)
			fdf->img->pixels[i] = 255;
	}
}

void ft_hook(void* param)
{
	mlx_t		*mlx = ((t_fdf *) param)->mlx;
	mlx_image_t	*image = ((t_fdf *) param)->img;
	t_fdf		*fdf = (t_fdf *) param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_KP_ADD))
	{
		fdf->zoom += 1;
		fdf->map->max_pxl = (fdf->map->rows + fdf->map->cols) * fdf->zoom;
		mlx_resize_image(image, fdf->map->max_pxl, fdf->map->max_pxl);
		clean_img(fdf);
		image->instances[0].x = (WIDTH - fdf->map->max_pxl) / 2;
		image->instances[0].y = (HEIGHT - fdf->map->max_pxl) / 2;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT) && fdf->zoom > 0)
	{
		fdf->zoom -= 1;
		fdf->map->max_pxl = (fdf->map->rows + fdf->map->cols) * fdf->zoom;
		mlx_resize_image(image, fdf->map->max_pxl, fdf->map->max_pxl);
		clean_img(fdf);
		image->instances[0].x = (WIDTH - fdf->map->max_pxl) / 2;
		image->instances[0].y = (HEIGHT - fdf->map->max_pxl) / 2;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_H))
	{
		fdf->h_mod += 0.01;
		clean_img(fdf);
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_L))
	{
		fdf->h_mod -= 0.01;
		clean_img(fdf);
		draw_map(fdf);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		return (ft_printf_fd(
				"Introduzca únicamente un archivo .fdf como argumento\n", 2), 1);
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
		return (ft_printf_fd(
				"Introduzca un archivo .fdf como argumento\n", 2), 1);
	fdf.fd = open(argv[1], O_RDONLY);
	if (fdf.fd == -1)
		return (ft_printf_fd(
				"Error al abrir el archivo\n", 2), 1);
	close(fdf.fd);
	fdf.zoom = STD_ZOOM;
	fdf.h_mod = STD_HMOD;
	fdf.brush = 1;
	fdf.style = 'o';
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF - Fernando Gómez", true);
	if (!fdf.mlx)
		ft_error();
	parse_map(argv[1], &fdf);
	if (!fdf.map)
		ft_error();
	fdf.img = mlx_new_image(fdf.mlx, fdf.img_w, fdf.img_h);
	if (!fdf.img)
		ft_error();
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	fdf.img->instances[0].x = (WIDTH - fdf.map->max_pxl) / 2;
	fdf.img->instances[0].y = (HEIGHT - fdf.map->max_pxl) / 2;
	clean_img(&fdf);
	draw_map(&fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}


// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>
// #include "../MLX42/include/MLX42/MLX42.h"
// #define WIDTH 256
// #define HEIGHT 256

// // Exit the program as failure.
// static void ft_error(void)
// {
// 	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// // Print the window width and height.
// static void ft_hook(void* param)
// {
// 	const mlx_t* mlx = param;

// 	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
// }

// int32_t	main(void)
// {

// 	// MLX allows you to define its core behaviour before startup.
// 	mlx_set_setting(MLX_MAXIMIZED, true);
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
// 	if (!mlx)
// 		ft_error();

// 	/* Do stuff */

// 	// Create and display the image.
// 	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		ft_error();

// 	// Even after the image is being displayed, we can still modify the buffer.
// 	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

// 	// Register a hook and pass mlx as an optional param.
// 	// NOTE: Do this before calling mlx_loop!
// 	mlx_loop_hook(mlx, ft_hook, mlx);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
