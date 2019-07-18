/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:21:11 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/14 18:03:56 by kcorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			pixel_put(t_mlx_var *mlx_var, int x, int y, int color)
{
	int			i;

	if (x < 0 || y < 0)
		return ;
	if (x >= mlx_var->screen.width || y >= mlx_var->screen.heigh)
		return ;
	i = (x * mlx_var->bits_per_pixel / 8) + (y * mlx_var->size_line);
	mlx_var->array[i++] = color;
	mlx_var->array[i++] = color >> 8;
	mlx_var->array[i++] = color >> 16;
	mlx_var->array[i] = 0;
}

int				get_color(int f_col, int s_col, int length, int i)
{
	int			r;
	int			g;
	int			b;

	r = F_RED + (S_RED - F_RED) * i / length;
	g = F_GREEN + (S_GREEN - F_GREEN) * i / length;
	b = F_BLUE + (S_BLUE - F_BLUE) * i / length;
	return ((r << 16) | (g << 8) | b);
}

void			display_line(t_mlx_var *mlx_var, int x1, int y1, int i)
{
	int			delta[2];
	int			sign[2];
	int			err[2];
	int			length;

	delta[X] = abs((int)mlx_var->maps->x_scaled - x1);
	delta[Y] = abs((int)mlx_var->maps->y_scaled - y1);
	sign[X] = x1 < (int)mlx_var->maps->x_scaled ? 1 : -1;
	sign[Y] = y1 < (int)mlx_var->maps->y_scaled ? 1 : -1;
	err[0] = delta[X] - delta[Y];
	length = (int)sqrt(delta[X] * delta[X] + delta[Y] * delta[Y]);
	pixel_put(mlx_var, mlx_var->maps->x_scaled,
	mlx_var->maps->y_scaled, mlx_var->rear->color);
	while (x1 != (int)mlx_var->maps->x_scaled ||
	y1 != (int)mlx_var->maps->y_scaled)
	{
		pixel_put(mlx_var, x1, y1,
		get_color(mlx_var->rear->color, mlx_var->maps->color, length, i++));
		err[1] = err[0] * 2;
		if (err[1] > -delta[Y] && ((err[0] -= delta[Y]) >= 0 || err[0] < 0))
			x1 += sign[X];
		if (err[1] < delta[X] && ((err[0] += delta[X]) >= 0 || err[0] < 0))
			y1 += sign[Y];
	}
}

void			display_pixels(t_mlx_var *mlx_var)
{
	mlx_var->iterator = mlx_var->maps->prev->count + 1;
	ft_bzero(mlx_var->array, mlx_var->screen.width * mlx_var->screen.heigh * 4);
	while (mlx_var->iterator-- && scalar_product_of_vectors(mlx_var))
	{
		mlx_var->maps->x_scaled = mlx_var->screen.width / 2
		+ mlx_var->linear_algebra.vectors.x;
		mlx_var->maps->y_scaled = mlx_var->screen.heigh / 2
		+ mlx_var->linear_algebra.vectors.y;
		if (mlx_var->maps->prev->x < mlx_var->maps->x)
		{
			mlx_var->rear = mlx_var->maps->prev;
			display_line(mlx_var, mlx_var->maps->prev->x_scaled,
			mlx_var->maps->prev->y_scaled, 1);
		}
		if (mlx_var->maps->upper && (mlx_var->rear = mlx_var->maps->upper))
		{
			display_line(mlx_var, mlx_var->maps->upper->x_scaled,
			mlx_var->maps->upper->y_scaled, 1);
		}
		mlx_var->maps = mlx_var->maps->next;
	}
	mlx_put_image_to_window(mlx_var->io, mlx_var->window, mlx_var->image, 0, 0);
	mlx_var->flags.hint ? add_hint(mlx_var) : 0;
}
