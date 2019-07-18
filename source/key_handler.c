/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 18:12:36 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/14 19:55:04 by kcorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	reset_mlx(t_mlx_var *mlx_var)
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
}

int		change_color(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 83 && (mlx_var->color.start = 0x20b2aa))
		mlx_var->color.final = 0xadff2f;
	else if (key_code == 84 && (mlx_var->color.start = 0xd2691e))
		mlx_var->color.final = 0xdcdcdc;
	else if (key_code == 85 && (mlx_var->color.start = 0x8b8b))
		mlx_var->color.final = 0x8b008b;
	else if (key_code == 86 && (mlx_var->color.start = 0x8b8b00))
		mlx_var->color.final = 0xff7256;
	else if (key_code == 87 && (mlx_var->color.start = 0x8b864e))
		mlx_var->color.final = 0xff3030;
	else
		return (0);
	initialize_color(mlx_var);
	return (1);
}

int		key_press2(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 4)
		if (!mlx_var->flags.hint)
			mlx_var->flags.hint = 1;
		else
			mlx_var->flags.hint = 0;
	else if (key_code == 2)
		if (!mlx_var->flags.debug_mode)
			mlx_var->flags.debug_mode = 1;
		else
			mlx_var->flags.debug_mode = 0;
	else if (key_code == 49)
		reset_mlx(mlx_var);
	else if (key_code == 53)
	{
		mlx_destroy_window(mlx_var->io, mlx_var->window);
		to_free_list(&mlx_var->maps, mlx_var->maps->prev->count);
		error_handler(EMERGENCY_EXIT);
	}
	else if (change_color(key_code, mlx_var))
		;
	else
		return (0);
	return (1);
}

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 69)
		mlx_var->screen.altitude *= 1.05;
	else if (key_code == 78)
		mlx_var->screen.altitude *= 0.95;
	else if (key_code == 116)
		mlx_var->mouse.rot_sensitivity += 0.0001;
	else if (key_code == 115)
		mlx_var->mouse.move_sensitivity += 0.1;
	else if (key_code == 121)
		mlx_var->mouse.rot_sensitivity > 0.0001 ?
		mlx_var->mouse.rot_sensitivity -= 0.0001 :
		(mlx_var->flags.hint = 1);
	else if (key_code == 119)
		mlx_var->mouse.move_sensitivity > 0.1 ?
		mlx_var->mouse.move_sensitivity -= 0.1 :
		(mlx_var->flags.hint = 1);
	else if (key_code == 6)
		mlx_var->flags.z_axis_mode == 0 ?
		mlx_var->flags.z_axis_mode = 1 :
		(mlx_var->flags.z_axis_mode = 0);
	else if (key_press2(key_code, mlx_var))
		;
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}

int		close_window(t_mlx_var *mlx_var)
{
	to_free_list(&mlx_var->maps, mlx_var->maps->prev->count);
	error_handler(USUAL_EXIT);
	return (0);
}
