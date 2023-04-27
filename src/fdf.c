/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 18:26:05 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void ft_error(void)
{
	ft_printf_fd("Error\n", 2);
	exit(EXIT_FAILURE);
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
		clean_img(fdf);
		get_img_size(fdf);
		mlx_resize_image(image, fdf->img_w, fdf->img_h);
		center_img(fdf);
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT) && fdf->zoom > 1)
	{
		fdf->zoom -= 1;
		clean_img(fdf);
		get_img_size(fdf);
		mlx_resize_image(image, fdf->img_w, fdf->img_h);
		center_img(fdf);
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
	if (mlx_is_key_down(mlx, MLX_KEY_B))
	{
		fdf->brush += 1;
		clean_img(fdf);
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_V) && fdf->brush > 1)
	{
		fdf->brush -= 1;
		clean_img(fdf);
		draw_map(fdf);
	}
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	check_args(argc, argv);
	fdf_init(&fdf, argv);
	fdf.mlx = mlx_init(WIDTH, HEIGHT, "FdF - Fernando Gómez", true);
	if (!fdf.mlx)
		ft_error();
	fdf.img = mlx_new_image(fdf.mlx, fdf.img_w, fdf.img_h);
	if (!fdf.img)
		ft_error();
	clean_img(&fdf);
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	center_img(&fdf);
	draw_map(&fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
