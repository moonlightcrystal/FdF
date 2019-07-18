/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 19:11:46 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/16 21:28:21 by kcorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	x_y_z_axis_rotation(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.basis_vectors[X][X] = COS_Y * COS_Z;
	mlx_var->linear_algebra.basis_vectors[X][Y] = -SIN_X * -SIN_Y * COS_Z
												+ COS_X * SIN_Z;
	mlx_var->linear_algebra.basis_vectors[X][Z] = -SIN_Y * COS_X * COS_Z
												+ SIN_Z * SIN_X;
	mlx_var->linear_algebra.basis_vectors[Y][X] = COS_Y * -SIN_Z;
	mlx_var->linear_algebra.basis_vectors[Y][Y] = -SIN_X * -SIN_Y * -SIN_Z
												+ COS_X * COS_Z;
	mlx_var->linear_algebra.basis_vectors[Y][Z] = -SIN_Z * -SIN_Y * COS_X
												+ SIN_X * COS_Z;
	mlx_var->linear_algebra.basis_vectors[Z][X] = SIN_Y;
	mlx_var->linear_algebra.basis_vectors[Z][Y] = -SIN_X * COS_Y;
	mlx_var->linear_algebra.basis_vectors[Z][Z] = COS_X * COS_Y;
}

int		scalar_product_of_vectors(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.vectors.x =
		((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][X])
		+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][X])
		+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][X]
		* mlx_var->screen.altitude)) * mlx_var->screen.scale
		+ mlx_var->linear_algebra.horizontal;
	mlx_var->linear_algebra.vectors.y =
		((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][Y])
		+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][Y])
		+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][Y]
		* mlx_var->screen.altitude)) * mlx_var->screen.scale
		+ mlx_var->linear_algebra.vertical;
	mlx_var->linear_algebra.vectors.z =
		((mlx_var->maps->x * mlx_var->linear_algebra.basis_vectors[X][Z])
		+ (mlx_var->maps->y * mlx_var->linear_algebra.basis_vectors[Y][Z])
		+ (mlx_var->maps->z * mlx_var->linear_algebra.basis_vectors[Z][Z]
		* mlx_var->screen.altitude)) * mlx_var->screen.scale;
	return (1);
}
