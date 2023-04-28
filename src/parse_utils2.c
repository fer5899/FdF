/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:38:17 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 14:06:42 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	count_rows(char *path)
{
	int		map_fd;
	int		n_lines;
	char	*line;

	map_fd = open(path, O_RDONLY);
	if (map_fd < 2)
		return (-1);
	n_lines = 0;
	line = get_next_line(map_fd);
	while (ft_strlen(line) > 0)
	{
		free(line);
		line = get_next_line(map_fd);
		n_lines++;
	}
	free(line);
	close(map_fd);
	return (n_lines);
}

void	set_initial_zoom(t_fdf *fdf)
{
	fdf->zoom = ft_minmax(WIDTH / fdf->img_w, HEIGHT / fdf->img_h, true) + 1;
	get_img_size(fdf);
}
