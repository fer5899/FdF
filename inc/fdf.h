/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:07:46 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/14 13:55:56 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
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
	t_map_pt	***pts;
	int			rows;
	int			cols;
}				t_map;

int		get_row_len(t_map_pt **pt);
void	iter_to_lower(unsigned int i, char *str);
int		get_arr_len(char **arr);
void	free_split(char	***strtab);
t_map	*parse_map(char *map_path);

#endif