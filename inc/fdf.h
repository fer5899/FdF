/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:07:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/26 18:11:33 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MIN_PT_SEP 4
# define STD_ZOOM 10

typedef struct s_map_pt
{
	int		row;
	int		col;
	int		x;
	int		y;
	int		z;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_map_pt;

typedef struct s_map
{
	t_map_pt		***pts;
	int				rows;
	int				cols;
	int				max_z;
	int				min_z;
	int				max_pxl;
	int				x_offset;
	int				y_offset;
}					t_map;

typedef struct s_fdf
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				fd;
	int				zoom;
	int				h_mod;
	char			style;
}				t_fdf;

int			get_row_len(t_map_pt **pt);
void		iter_to_lower(unsigned int i, char *str);
int			get_arr_len(char **arr);
void		free_split(char	***strtab);
void		parse_map(char *map_path, t_fdf *fdf);
int			get_r(int rgba);
int			get_g(int rgba);
int			get_b(int rgba);
int			get_rgba(int r, int g, int b, int a);
void		draw_pt(t_fdf *fdf, t_map_pt *pt, int brush_size);
void		draw_line(t_fdf *fdf, t_map_pt *pt1, t_map_pt *pt2, int brush_size);
t_map_pt	*init_pt(int x, int y, int z, unsigned int rgba);
void		set_colors(t_fdf *fdf, t_map_pt *pt, t_map_pt *pt1, t_map_pt *pt2);
void		draw_map(t_fdf *fdf, int brush_size);
int			count_rows(char *path);

#endif