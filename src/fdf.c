/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/22 19:47:06 by fgomez-d         ###   ########.fr       */
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
	if (open(argv[1], O_RDONLY) == -1)
		return (ft_printf_fd(
				"Error al abrir el archivo\n", 2), 1);

	fdf.mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!fdf.mlx)
		ft_error();
	parse_map(argv[1], &fdf);
	if (!fdf.map)
		ft_error();
	fdf.img = mlx_new_image(fdf.mlx, 256, 100);
	if (!fdf.img)
		ft_error();
	mlx_image_to_window(fdf.mlx, fdf.img, 10, 10);
	
	int i = -1;
	while (++i < 256*100*4) // map->rows*map->cols
	{
		fdf.img->pixels[i] = 0;
		if (i % 4 == 3)
			fdf.img->pixels[i] = 0;
	}
	fdf.color = 'g';
	draw_line(&fdf, init_pt(10, 50, 9, get_rgba(255,100,0,255)), init_pt(100, 50, 9, get_rgba(0,0,255,255)), 6);

	mlx_loop_hook(fdf.mlx, ft_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
