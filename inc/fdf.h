/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:07:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/18 20:26:47 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>

typedef struct s_map_pt
{
	int	x;
	int	y;
	int	z;
	int	r;
	int	g;
	int	b;
	int	a; // comprobar si pueden llegar valores de opacidad en el mapa
}	t_map_pt;

typedef struct s_map
{
	t_map_pt		***pts;
	int				rows;
	int				cols;
}					t_map;

typedef struct s_fdf
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*img;
}				t_fdf;

int			get_row_len(t_map_pt **pt);
void		iter_to_lower(unsigned int i, char *str);
int			get_arr_len(char **arr);
void		free_split(char	***strtab);
void		parse_map(char *map_path, t_fdf *fdf);
int 		get_r(int rgba);
int 		get_g(int rgba);
int 		get_b(int rgba);
int 		get_a(int rgba);
int 		get_rgba(int r, int g, int b, int a);
void		draw_pt(t_map *map, t_map_pt *pt);
t_map_pt	*init_pt(int x, int y, int z, unsigned int rgba);

#endif