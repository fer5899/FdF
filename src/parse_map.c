/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:27:20 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 10:34:55 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	init_map(t_fdf *fdf, t_map_pt **fst_row)
{
	if (fst_row == NULL)
		return (0);
	if (fdf->map->cols == 0)
		return (free(fdf->map), 0);
	fdf->map->pts = (t_map_pt ***) ft_calloc(fdf->map->rows,
			sizeof(t_map_pt **));
	if (fdf->map->pts == NULL)
		return (free(fdf->map), 0);
	fdf->map->pts[0] = fst_row;
	fdf->map->max_z = 0;
	fdf->map->min_z = 0;
	return (1);
}

t_map_pt	*parse_pt(char **pt_data, int row, int col)
{
	t_map_pt	*pt;
	int			rgb;

	pt = (t_map_pt *) ft_calloc(1, sizeof(t_map_pt));
	pt->row = row;
	pt->col = col;
	if (pt_data == NULL)
		return (pt);
	pt->a = 255;
	pt->z = ft_atoi(pt_data[0]);
	if (pt_data[1] != NULL)
	{
		ft_striteri(pt_data[1], iter_to_lower);
		rgb = ft_atoi_base(pt_data[1] + 2, "0123456789abcdef");
		pt->r = ((rgb >> 16) & 0xFF);
		pt->g = ((rgb >> 8) & 0xFF);
		pt->b = ((rgb >> 0) & 0xFF);
	}
	return (pt);
}

t_map_pt	**parse_row(t_fdf *fdf, int map_fd, int i_row)
{
	t_map_pt	**row;
	char		*line;
	char		**split;
	int			i_col;
	int			cols;

	line = get_next_line(map_fd);
	if (!line)
		return (NULL);
	split = ft_split(line, ' ');
	if (!split)
		return (NULL);
	cols = get_arr_len(split);
	if (cols == 0)
		return (free_split(&split), NULL);
	fdf->map->cols = cols;
	row = (t_map_pt **) ft_calloc(cols, sizeof(t_map_pt *));
	i_col = 0;
	while (split[i_col] != NULL)
	{
		row[i_col] = parse_pt(ft_split(split[i_col], ','),
				i_row, i_col);
		i_col++;
	}
	return (row);
}

int	add_row(t_fdf *fdf, int map_fd, int i_row)
{
	t_map_pt	**row;

	row = parse_row(fdf, map_fd, i_row);
	if (!row)
		return (0);
	fdf->map->pts[i_row] = row;
	return (1);
}

void	parse_map(char *map_path, t_fdf *fdf)
{
	int			map_fd;
	t_map_pt	**row;
	int			i_row;

	fdf->map = (t_map *) ft_calloc(1, sizeof(t_map));
	if (!(fdf->map))
		return ;
	fdf->map->rows = count_rows(map_path);
	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return ;
	row = parse_row(fdf, map_fd, 0);
	if (!row || !init_map(fdf, row))
	{
		free(fdf->map->pts); // Reduce this with free functions
		free(fdf->map);
	}
	i_row = 0;
	while (++i_row < fdf->map->rows)
	{
		add_row(fdf, map_fd, i_row); // protect this
	}
	close(map_fd);
	get_img_size(fdf);
	set_initial_zoom(fdf);
}
