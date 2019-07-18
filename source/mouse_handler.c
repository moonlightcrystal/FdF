/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:20:19 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/18 13:54:55 by kcorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse.left_pressed = 1;
	else if (button == 2)
		mlx_var->mouse.right_pressed = 1;
	else if (button == 3)
		mlx_var->screen.scale = mlx_var->screen.main_scale;
	else if (button == 4)
		mlx_var->screen.scale *= 1.05;
	else if (button == 5)
		mlx_var->screen.scale *= 0.95;
	mlx_var->mouse.x = x;
	mlx_var->mouse.y = y;
	display_pixels(mlx_var);
	return (0);
}

int		mouse_release(int button, int x, int y, t_mlx_var *mlx_var)
{
	if (button == 1)
		mlx_var->mouse.left_pressed = 0;
	else if (button == 2)
		mlx_var->mouse.right_pressed = 0;
	x++;
	y++;
	return (0);
}

int		mouse_move(int x, int y, t_mlx_var *mlx_var)
{
	if (mlx_var->mouse.left_pressed || mlx_var->mouse.right_pressed)
	{
		if (mlx_var->mouse.left_pressed)
		{
			mlx_var->linear_algebra.angle_x +=
			-(mlx_var->mouse.rot_sensitivity * (y - mlx_var->mouse.y));
			mlx_var->linear_algebra.angle_y +=
			(mlx_var->mouse.rot_sensitivity * (x - mlx_var->mouse.x));
		}
		if (mlx_var->mouse.right_pressed)
		{
			mlx_var->flags.z_axis_mode ? mlx_var->linear_algebra.angle_z +=
			mlx_var->mouse.rot_sensitivity * (y - mlx_var->mouse.y) +
			mlx_var->mouse.rot_sensitivity * (x - mlx_var->mouse.x) :
			(mlx_var->linear_algebra.vertical +=
			mlx_var->mouse.move_sensitivity * (y - mlx_var->mouse.y)) &&
			(mlx_var->linear_algebra.horizontal +=
			mlx_var->mouse.move_sensitivity * (x - mlx_var->mouse.x));
		}
		mlx_var->mouse.y = y;
		mlx_var->mouse.x = x;
		x_y_z_axis_rotation(mlx_var);
		display_pixels(mlx_var);
	}
	return (0);
}

int		expose(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.horizontal = 0;
	mlx_var->linear_algebra.vertical = 0;
	mlx_var->linear_algebra.angle_x = 1.100;
	mlx_var->linear_algebra.angle_y = 0;
	mlx_var->linear_algebra.angle_z = -0.880;
	mlx_var->mouse.move_sensitivity = 1.0;
	mlx_var->mouse.rot_sensitivity = 0.0030;
	mlx_var->flags.z_axis_mode = 1;
	mlx_var->flags.debug_mode = 0;
	mlx_var->screen.altitude = 1.0;
	mlx_var->flags.hint = 0;
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}
