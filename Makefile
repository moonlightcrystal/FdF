# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcorie <kcorie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/03 18:19:29 by kcorie          #+#    #+#              #
#    Updated: 2019/07/18 13:57:05 by kcorie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

SOURCE_DIR	= source
GNL_DIR		= getnextline
LIBFT_DIR	= $(GNL_DIR)/Libft
MLX_DIR		= minilibx_macos

MLX_INCLUDE	= usr/local/include
GNL_INCL	= $(GNL_DIR)/includes
LIBFT_INCL	= $(LIBFT_DIR)/includes
INCLUDES	= -I./$(GNL_INCL) -I./$(LIBFT_INCL) -I./includes

LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

FILES		= $(addprefix $(SOURCE_DIR)/, fdf.c errors_handler.c lists_functions.c read_and_write_coordinates.c linear_algebra.c hint.c display_pixels.c key_handler.c mouse_handler.c)

OBJ_FILES	= ${FILES:%.c=%.o}

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

MLX_FLAGS	= -lmlx -framework Ope4nGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(INCLUDES) $(GNL_DIR)/source/get_next_line.c $^ -o $@

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -I./$(MLX_INCLUDE) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re:	fclean all