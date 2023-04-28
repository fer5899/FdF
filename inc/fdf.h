/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:07:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 10:34:49 by fgomez-d         ###   ########.fr       */
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
# define STD_HMOD 0.1

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
	int				min_x;
	int				max_x;
	int				min_y;
	int				max_y;
	int				max_z;
	int				min_z;
	int				max_pxl;
}					t_map;

typedef struct s_fdf
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				fd;
	int				zoom;
	double			h_mod;
	char			style;
	char			persp;
	int				brush;
	int				img_h;
	int				img_w;
	double			x_rad;
	double			y_rad;
	double			z_rad;
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
void		draw_pt(t_fdf *fdf, t_map_pt *pt);
void		draw_line(t_fdf *fdf, t_map_pt *pt1, t_map_pt *pt2);
t_map_pt	*init_pt(int x, int y, int z, unsigned int rgba);
void		set_colors(t_fdf *fdf, t_map_pt *pt, t_map_pt *pt1, t_map_pt *pt2);
void		draw_map(t_fdf *fdf);
int			count_rows(char *path);
void		calc_pts_xy(t_fdf *fdf, t_map_pt *pt);
void		fdf_map_iter(t_fdf *fdf, void (*f)(t_fdf *, t_map_pt *));
void		get_img_size(t_fdf *fdf);
void		check_args(int argc, char **argv);
void		fdf_init(t_fdf *fdf, char **argv);
void		clean_img(t_fdf *fdf);
void		center_img(t_fdf *fdf);
void		set_initial_zoom(t_fdf *fdf);

#endif