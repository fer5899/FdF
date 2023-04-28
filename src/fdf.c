/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:45:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:29:26 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static void	ft_error(void)
{
	ft_printf_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

void	leaks(void)
{
	system("leaks -q fdf");
}

void	print_ptrs(void *content)
{
	ft_printf("%p\n", content);
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
	mlx_key_hook(fdf.mlx, &disc_hook, &fdf);
	mlx_loop_hook(fdf.mlx, cont_hook, &fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
