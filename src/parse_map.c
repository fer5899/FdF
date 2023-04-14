/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 09:27:20 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/14 13:55:29 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	init_map(t_map *map, t_map_pt **fst_row)
{
	if (fst_row == NULL)
		return (0);
	map->rows = 1;
	if (map->cols == 0)
		return (free(map), 0);
	map->pts = (t_map_pt ***) ft_calloc(1, sizeof(t_map_pt **));
	if (map->pts == NULL)
		return (free(map), 0);
	map->pts[0] = fst_row;
	return (1);
}

t_map_pt	*init_pt(char **pt_data, int row, int col)
{
	t_map_pt	*pt;
	int			rgb;

	pt = (t_map_pt *) ft_calloc(1, sizeof(t_map_pt));
	pt->x = col;
	pt->y = row;
	if (pt_data == NULL)
		return (pt);
	if (pt_data[1] == NULL)
	{
		pt->r = 255;
		pt->g = 255;
		pt->b = 255;
	}
	else
	{
		ft_striteri(pt_data[1], iter_to_lower);
		rgb = ft_atoi_base(pt_data[1] + 2, "0123456789abcdef");
		pt->r = ((rgb >> 16) & 0xFF);
		pt->g = ((rgb >> 8) & 0xFF);
		pt->b = ((rgb >> 0) & 0xFF);
	}
	pt->a = 255; // Comprobar si pueden entrar valores de opacidad por mapa
	pt->z = ft_atoi(pt_data[0]);
	return (pt);
}

t_map_pt	**parse_row(t_map *map, int map_fd, int i_row)
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
	map->cols = cols;
	row = (t_map_pt **) ft_calloc(cols, sizeof(t_map_pt *));
	i_col = 0;
	while (split[i_col] != NULL)
	{
		row[i_col] = init_pt(ft_split(split[i_col], ','),
				i_row, i_col);
		i_col++;
	}
	return (row);
}

int	add_row(t_map *map, int map_fd, int i_row)
{
	t_map_pt	**row;

	row = parse_row(map, map_fd, i_row);
	if (!row)
		return (0);
	map->pts[i_row] = row;
	map->rows += 1;
	return (1);
}

t_map	*parse_map(char *map_path)
{
	int			map_fd;
	t_map_pt	**row;
	t_map		*map;
	int			i_row;

	map_fd = open(map_path, O_RDONLY);
	if (map_fd == -1)
		return (NULL);
	map = (t_map *) ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	row = parse_row(map, map_fd, 0);
	if (!row || !init_map(map, row))
		return (free(map->pts), free(map), NULL);
	i_row = 1;
	while (add_row(map, map_fd, i_row))
		i_row++;
	return (map);
}
