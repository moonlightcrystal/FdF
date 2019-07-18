/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 15:23:20 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/14 18:45:09 by kcorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			add_hint(t_mlx_var *mlx_var)
{
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20, 0xfffafa, "Control:");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 15, 0xfffafa,
	"Zoom: Scroll Up(+) Scrool Down(-)");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 30, 0xfffafa,
	"Rotate: Mouse move(right, left button press)");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 45, 0xfffafa,
	"Move: 'z' button then right button mouse move");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 60, 0xfffafa, "Debug mode: 'e'");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 75, 0xfffafa,
	"Change color: 1, 2, 3, 4, 5 button at the left panel");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 90, 0xfffafa,
	"Change sensitivity rotate: Up(+), Down(-)");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 105, 0xfffafa,
	"Change sensitivity move: Up_end(+), Down_end(-)");
	mlx_string_put(mlx_var->io, mlx_var->window, mlx_var->screen.width / 20,
	mlx_var->screen.heigh / 20 + 120, 0xfffafa, "Turn off hint: 'h'");
}
