/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:11:31 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/14 18:10:24 by kcorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fasten_event_handlers(t_mlx_var *mlx_var)
{
	mlx_hook(mlx_var->window, 2, 0, key_press, mlx_var);
	mlx_hook(mlx_var->window, 4, 0, mouse_press, mlx_var);
	mlx_hook(mlx_var->window, 5, 0, mouse_release, mlx_var);
	mlx_hook(mlx_var->window, 6, 0, mouse_move, mlx_var);
	mlx_hook(mlx_var->window, 12, 0, expose, mlx_var);
	mlx_hook(mlx_var->window, 17, 0, close_window, mlx_var);
}

int				initialize_color(t_mlx_var *mlx_var)
{
	mlx_var->iterator = mlx_var->maps->prev->count + 1;
	while (mlx_var->iterator--)
	{
		if (mlx_var->maps->z == mlx_var->color.lowest->z)
			mlx_var->maps->color = mlx_var->color.start;
		else if (mlx_var->maps->z == mlx_var->color.highest->z)
			mlx_var->maps->color = mlx_var->color.final;
		else
			mlx_var->maps->color = get_color(mlx_var->color.start,
			mlx_var->color.final,
			mlx_var->color.highest->z - mlx_var->color.lowest->z,
			mlx_var->maps->z - mlx_var->color.lowest->z);
		mlx_var->maps = mlx_var->maps->next;
	}
	return (1);
}

t_mlx_var		*mlx_var_init(int argc, char **argv, int fd)
{
	t_mlx_var	*mlx_var;

	mlx_var = (t_mlx_var *)malloc(sizeof(t_mlx_var));
	mlx_var->screen.width = 1500;
	mlx_var->screen.heigh = 1300;
	if (argc == 4)
	{
		mlx_var->screen.width = ft_atoi(argv[2]);
		mlx_var->screen.heigh = ft_atoi(argv[3]);
		if (mlx_var->screen.heigh < 100 || mlx_var->screen.width < 100)
			return (NULL);
	}
	mlx_var->color.start = 0xd2691e;
	mlx_var->color.final = 0xdcdcdc;
	(mlx_var->maps = initialize_maps(fd, mlx_var)) && center_maps(mlx_var);
	initialize_color(mlx_var);
	mlx_var->screen.scale = cbrt((mlx_var->screen.width * mlx_var->screen.heigh)
	/ (mlx_var->maps->prev->x * mlx_var->maps->prev->y));
	mlx_var->screen.scale < 1 ? mlx_var->screen.scale = 1 : 0;
	mlx_var->screen.main_scale = mlx_var->screen.scale;
	return (mlx_var);
}

int				main(int argc, char **argv)
{
	t_mlx_var	*mlx_var;
	int			fd;

	if (argc < 2)
		error_handler(INCORRECT_ARGS);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		error_handler(FILE_ERROR);
	if (!(mlx_var = mlx_var_init(argc, argv, fd)))
		error_handler(MLX_VAR_ERROR);
	if (!(mlx_var->io = mlx_init()))
		error_handler(CONNECT_ERROR);
	if (!(mlx_var->window = mlx_new_window(mlx_var->io,
	mlx_var->screen.width, mlx_var->screen.heigh, argv[1])))
		error_handler(WINDOW_ERROR);
	if (!(mlx_var->image = mlx_new_image(mlx_var->io,
	mlx_var->screen.width, mlx_var->screen.heigh)))
		error_handler(IMAGE_ERROR);
	if (!(mlx_var->array = mlx_get_data_addr(mlx_var->image,
	&mlx_var->bits_per_pixel, &mlx_var->size_line, &mlx_var->endian)))
		error_handler(ARRAY_ERROR);
	fasten_event_handlers(mlx_var);
	mlx_loop(mlx_var->io);
}
