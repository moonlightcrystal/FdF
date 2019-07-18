/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcorie <kcorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:53:08 by kcorie          #+#    #+#             */
/*   Updated: 2019/07/18 13:54:01 by kcorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

typedef enum			e_coord_manager
{
	X,
	Y,
	Z,
}						t_coord_manager;

typedef enum			e_list_manager
{
	HEAD,
	ITER,
	TEMP,
}						t_list_manager;

typedef struct			s_flags
{
	int					debug_mode;
	int					hint;
	int					z_axis_mode;
}						t_flags;

typedef struct			s_screen
{
	int					width;
	int					heigh;
	long double			scale;
	long double			altitude;
	long double			main_scale;
}						t_screen;

typedef struct			s_vectors
{
	long double			x;
	long double			y;
	long double			z;
}						t_vectors;

typedef struct			s_linear_algebra
{
	long double			basis_vectors[3][3];
	long double			angle_x;
	long double			angle_y;
	long double			angle_z;
	long double			vertical;
	long double			horizontal;
	t_vectors			vectors;
}						t_linear_algebra;

typedef struct			s_mouse
{
	int					left_pressed;
	int					right_pressed;
	long double			x;
	long double			y;
	long double			rot_sensitivity;
	long double			move_sensitivity;
}						t_mouse;

typedef struct			s_coords
{
	int					count;
	int					color;
	long double			x;
	long double			y;
	long double			z;
	long double			z_tmp;
	long double			x_scaled;
	long double			y_scaled;
	struct s_coords		*next;
	struct s_coords		*prev;
	struct s_coords		*upper;
}						t_coords;

typedef struct			s_color
{
	int					start;
	int					final;
	t_coords			*highest;
	t_coords			*lowest;
}						t_color;

typedef	struct			s_mlx_var
{
	void				*io;
	void				*window;
	void				*image;
	char				*array;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					iterator;
	t_flags				flags;
	t_screen			screen;
	t_linear_algebra	linear_algebra;
	t_mouse				mouse;
	t_color				color;
	t_coords			*rear;
	t_coords			*maps;
}						t_mlx_var;

/*
** Error_manager_macros
*/

# define CONNECT_ERROR	1
# define WINDOW_ERROR	2
# define IMAGE_ERROR	3
# define ARRAY_ERROR	4
# define EMERGENCY_EXIT	5
# define USUAL_EXIT		6
# define MLX_VAR_ERROR	7
# define INCORRECT_ARGS	8
# define FILE_ERROR		9
# define MEMORY_ERROR	10

/*
** Linear_algebra(Matrix calculations)
*/

# define COS_X			cos(mlx_var->linear_algebra.angle_x)
# define COS_Y			cos(mlx_var->linear_algebra.angle_y)
# define COS_Z			cos(mlx_var->linear_algebra.angle_z)

# define SIN_X			sin(mlx_var->linear_algebra.angle_x)
# define SIN_Y			sin(mlx_var->linear_algebra.angle_y)
# define SIN_Z			sin(mlx_var->linear_algebra.angle_z)

/*
** Color manager
*/

# define F_RED			((f_col >> 16) & 0xff)
# define F_GREEN		((f_col >> 8) & 0xff)
# define F_BLUE			(f_col & 0xff)
# define S_RED			((s_col >> 16) & 0xff)
# define S_GREEN		((s_col >> 8) & 0xff)
# define S_BLUE			(s_col & 0xff)

/*
** Declaretes all functions
*/

t_coords				*new_point_in_space(long double x, long double y,
						long double z);
t_coords				*initialize_maps(int fd, t_mlx_var *mlx_var);
void					add_frame(t_mlx_var *mlx_var);
void					x_axis_rotation(t_mlx_var *mlx_var);
void					y_axis_rotation(t_mlx_var *mlx_var);
void					z_axis_rotation(t_mlx_var *mlx_var);
void					x_y_axis_rotation(t_mlx_var *mlx_var);
void					x_y_z_axis_rotation(t_mlx_var *mlx_var);
void					view_from_above(t_mlx_var *mlx_var);
void					to_mirror_image(t_mlx_var *mlx_var);
int						scalar_product_of_vectors(t_mlx_var *mlx_var);
void					to_tie_list(t_coords **list);
void					error_handler(int code_of_errors);
void					line(t_mlx_var *mlx_var, int x0, int x1, int y0,
						int y1);
void					display_pixels(t_mlx_var *mlx_var);
void					change_altitude(t_mlx_var *mlx_var, int up);
void					pixel_put(t_mlx_var *mlx_var, int x, int y, int colour);
void					add_hint(t_mlx_var *mlx_var);
void					to_free_list(t_coords **list, int size);
int						initialize_color(t_mlx_var *mlx_var);
int						center_maps(t_mlx_var *mlx_var);
int						key_press(int key_code, t_mlx_var *mlx_var);
int						mouse_press(int button, int x, int y,
						t_mlx_var *mlx_var);
int						mouse_release(int button, int x, int y,
						t_mlx_var *mlx_var);
int						mouse_move(int x, int y, t_mlx_var *mlx_var);
int						expose(t_mlx_var *mlx_var);
int						close_window(t_mlx_var *mlx_var);
int						get_color(int f_col, int s_col, int length, int i);

#endif
