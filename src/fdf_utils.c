/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 13:20:25 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/27 18:21:20 by fgomez-d         ###   ########.fr       */
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
	fdf->zoom = STD_ZOOM;
	fdf->h_mod = STD_HMOD;
	fdf->brush = 1;
	fdf->style = 'g';
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
