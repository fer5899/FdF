/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cursor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez-d <fgomez-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 20:10:54 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/04/13 20:57:55 by fgomez-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/MLX42/MLX42_Int.h"

//= Public =//

void* mlx_create_std_cursor(cursor_t type)
{
	MLX_ASSERT(type >= MLX_CURSOR_ARROW && type < MLX_CURSOR_VRESIZE, "Invalid standart cursor type");

	GLFWcursor* cursor;
	if ((cursor = glfwCreateStandardCursor(type)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

void* mlx_create_cursor(mlx_texture_t* texture)
{
	MLX_NONNULL(texture);

	GLFWcursor* cursor;
	if ((cursor = glfwCreateCursor((GLFWimage*)texture, 0, 0)))
		return (cursor);
	return ((void *)mlx_error(MLX_MEMFAIL));
}

void mlx_set_cursor(mlx_t* mlx, void* cursor)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(cursor);

	glfwSetCursor(mlx->window, cursor);
}

void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode)
{
	MLX_NONNULL(mlx);

	glfwSetInputMode(mlx->window, GLFW_CURSOR, mode);
}
