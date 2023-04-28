/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:59:39 by fgomez-d          #+#    #+#             */
/*   Updated: 2023/04/28 13:09:33 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	apply_movement(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_UP))
	{
		fdf->img->instances[0].y += 5;
		fdf->mov_y += 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_DOWN))
	{
		fdf->img->instances[0].y -= 5;
		fdf->mov_y -= 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_LEFT))
	{
		fdf->img->instances[0].x += 5;
		fdf->mov_x += 5;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_RIGHT))
	{
		fdf->img->instances[0].x -= 5;
		fdf->mov_x -= 5;
	}
}

void	apply_zoom(t_fdf *fdf)
{
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_ADD))
	{
		fdf->mov_x *= (fdf->zoom + 1) / (double)(fdf->zoom);
		fdf->mov_y *= (fdf->zoom + 1) / (double)(fdf->zoom);
		fdf->zoom += 1;
	}
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_KP_SUBTRACT) && fdf->zoom > 1)
	{
		fdf->mov_x *= (fdf->zoom - 1) / (double)(fdf->zoom);
		fdf->mov_y *= (fdf->zoom - 1) / (double)(fdf->zoom);
		fdf->zoom -= 1;
	}
}

void	cont_hook(void *param)
{
	t_fdf		*fdf;

	fdf = (t_fdf *) param;
	apply_zoom(fdf);
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_H))
		fdf->h_mod += 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_L))
		fdf->h_mod -= 0.01;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_D))
		fdf->z_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_A))
		fdf->z_rad -= 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_Q))
		fdf->y_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_E))
		fdf->y_rad -= 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_W))
		fdf->x_rad += 0.1;
	if (mlx_is_key_down(fdf->mlx, MLX_KEY_S))
		fdf->x_rad -= 0.1;
	draw_map(fdf);
	apply_movement(fdf);
}

void	disc_hook(mlx_key_data_t key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) param;
	if (key.key == MLX_KEY_ESCAPE && key.action == MLX_PRESS)
		mlx_close_window(fdf->mlx);
	if (key.key == MLX_KEY_R && key.action == MLX_PRESS)
	{
		fdf->mov_x = 0;
		fdf->mov_y = 0;
		fdf->x_rad = 0;
		fdf->y_rad = 0;
		fdf->z_rad = 0;
	}
	if (key.key == MLX_KEY_I && key.action == MLX_PRESS)
		fdf->persp = 'I';
	if (key.key == MLX_KEY_C && key.action == MLX_PRESS)
		fdf->persp = 'C';
	if (key.key == MLX_KEY_P && key.action == MLX_PRESS)
		fdf->persp = 'P';
	if (48 <= key.key && key.key <= 57 && key.action == MLX_PRESS)
		fdf->color = key.key - 48;
	if (key.key == MLX_KEY_B && key.action == MLX_PRESS)
		fdf->brush += 1;
	if (key.key == MLX_KEY_V && key.action == MLX_PRESS && fdf->brush > 1)
		fdf->brush -= 1;
}
