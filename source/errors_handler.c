/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:47:45 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/18 13:49:38 by kcorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error_handler(int code_of_errors)
{
	if (code_of_errors == CONNECT_ERROR)
		ft_putendl("Connection hasn't been established, exit...\n");
	else if (code_of_errors == WINDOW_ERROR)
		ft_putendl("Window hasn't been created, exit...\n");
	else if (code_of_errors == IMAGE_ERROR)
		ft_putendl("Image object hasn't been created, exit...\n");
	else if (code_of_errors == ARRAY_ERROR)
		ft_putendl("Data addres hasn't been got, exit...\n");
	else if (code_of_errors == EMERGENCY_EXIT)
		ft_putendl("The program has been forsibly completed...\n");
	else if (code_of_errors == USUAL_EXIT)
		ft_putendl("The program has been closed...\n");
	else if (code_of_errors == MLX_VAR_ERROR)
		ft_putendl("Main mlx variable hasn't been initializied, exit...\n");
	else if (code_of_errors == INCORRECT_ARGS)
		ft_putendl("Number of args is zero, exit...\n");
	else if (code_of_errors == FILE_ERROR)
		ft_putendl("File hasn't been opened, exit...\n");
	else if (code_of_errors == MEMORY_ERROR)
		ft_putendl("Memory hasn't been allocated, exit...\n");
	exit(1);
}
