/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 12:52:20 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_error(void)
{
	ft_printf_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_hook(void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *) param;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(fdf->mlx);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		fdf->mov_x *= (fdf->zoom + 1) / (double)(fdf->zoom);
		fdf->mov_y *= (fdf->zoom + 1) / (double)(fdf->zoom);
		fdf->zoom += 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT) && fdf->zoom > 1)
	{
		fdf->mov_x *= (fdf->zoom - 1) / (double)(fdf->zoom);
		fdf->mov_y *= (fdf->zoom - 1) / (double)(fdf->zoom);
		fdf->zoom -= 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_H))
		fdf->h_mod += 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_L))
		fdf->h_mod -= 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->z_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->z_rad -= 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->y_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->y_rad -= 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->x_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->x_rad -= 0.1;
	draw_map(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	{
		fdf->img->instances[0].y += 5;
		fdf->mov_y += 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
	{
		fdf->img->instances[0].y -= 5;
		fdf->mov_y -= 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
	{
		fdf->img->instances[0].x += 5;
		fdf->mov_x += 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
	{
		fdf->img->instances[0].x -= 5;
		fdf->mov_x -= 5;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->mov_x = 0;
		fdf->mov_y = 0;
		fdf->x_rad = 0;
		fdf->y_rad = 0;
		fdf->z_rad = 0;
		draw_map(fdf);
	}
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		fdf->persp = 'I';
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		fdf->persp = 'C';
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
		fdf->persp = 'P';
	if (48 <= keydata.key && keydata.key <= 57 && keydata.action == MLX_PRESS)
		fdf->color = keydata.key - 48;
	if (keydata.key == MLX_KEY_B && keydata.action == MLX_PRESS)
		fdf->brush += 1;
	if (keydata.key == MLX_KEY_V && keydata.action == MLX_PRESS
		&& fdf->brush > 1)
		fdf->brush -= 1;
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
	mlx_image_to_window(fdf.mlx, fdf.img, 0, 0);
	draw_map(&fdf);
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
