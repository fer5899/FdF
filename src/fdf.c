/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 10:17:40 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_error(void)
{
	ft_printf_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	print_pt(t_fdf *fdf, t_map_pt *pt)
{
	// if (pt->col == 0 && pt->row == 0)
	// {
	// 	get_img_size(fdf);
	// }
	ft_printf("(%d, %d) ", pt->x, pt->y);
	if (pt->col == fdf->map->cols - 1)
		ft_printf("\n");
	if (pt->col == fdf->map->cols - 1 && pt->row == fdf->map->rows - 1)
	{
		ft_printf("saved img size: %d %d\n", fdf->img_w, fdf->img_h);
	}
	
}

void	ft_hook(void *param)
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
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_KP_SUBTRACT) && fdf->zoom > 1)
	{
		fdf->zoom -= 1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_H))
	{
		fdf->h_mod += 0.01;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_L))
	{
		fdf->h_mod -= 0.01;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_B))
	{
		fdf->brush += 1;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_V) && fdf->brush > 1)
	{
		fdf->brush -= 1;
		draw_map(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		fdf->z_rad += 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		fdf->z_rad -= 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_Q))
	{
		fdf->y_rad += 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_E))
	{
		fdf->y_rad -= 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		fdf->x_rad += 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		fdf->x_rad -= 0.1;
		draw_map(fdf);
		center_img(fdf);
	}
}

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	t_fdf *fdf;

	fdf = (t_fdf *) param;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		fdf->x_rad = 0;
		fdf->y_rad = 0;
		fdf->z_rad = 0;
		draw_map(fdf);
		center_img(fdf);
	}
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
	{
		fdf->persp = 'I';
		draw_map(fdf);
		center_img(fdf);
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		fdf->persp = 'C';
		draw_map(fdf);
		center_img(fdf);
	}
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		fdf->persp = 'P';
		draw_map(fdf);
		center_img(fdf);
	}
	

	// // If we RELEASE the 'K' key, print "World".
	// if (keydata.key == MLX_KEY_K && keydata.action == MLX_RELEASE)
	// 	puts("World");

	// // If we HOLD the 'L' key, print "!".
	// if (keydata.key == MLX_KEY_L && keydata.action == MLX_REPEAT)
	// 	puts("!");
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
	mlx_key_hook(fdf.mlx, &my_keyhook, &fdf);
	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
