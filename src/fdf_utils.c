/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:20:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 10:38:38 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	check_args(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
	{
		ft_printf_fd(
			"Introduzca únicamente un archivo .fdf como argumento\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strnstr(argv[1], ".fdf", ft_strlen(argv[1])) == NULL)
	{
		ft_printf_fd(
				"Introduzca un archivo .fdf como argumento\n", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd("Error al abrir el archivo\n", 2);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	fdf_init(t_fdf *fdf, char **argv)
{
	fdf->zoom = 1;
	fdf->h_mod = STD_HMOD;
	fdf->brush = 1;
	fdf->style = 'g';
	fdf->persp = 'I';
	parse_map(argv[1], fdf);
	if (!fdf->map)
	{
		ft_printf_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	fdf_map_iter(t_fdf *fdf, void (*f)(t_fdf *, t_map_pt *))
{
	int			row;
	int			col;
	t_map_pt	*pt;

	row = -1;
	col = -1;
	while (++row < fdf->map->rows)
	{
		while (++col < fdf->map->cols)
		{
			pt = fdf->map->pts[row][col];
			f(fdf, pt);
		}
		col = -1;
	}
}

void	clean_img(t_fdf *fdf)
{
	int	i;

	i = -1;
	while (++i < (int)(fdf->img->height * fdf->img->width * 4))
		fdf->img->pixels[i] = 0;
}

void	center_img(t_fdf *fdf)
{
	fdf->img->instances[0].x = (WIDTH - fdf->img_w) / 2;
	fdf->img->instances[0].y = (HEIGHT - fdf->img_h) / 2;
}
