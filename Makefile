# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/22 23:12:10 by pbondoer          #+#    #+#              #
#    Updated: 2016/12/13 17:56:28 by pbondoer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= wolf3d
OS		= $(shell uname)

# directories
SRCDIR	= ./src
INCDIR	= ./includes
OBJDIR	= ./obj

# src / obj files
SRC		= main.c \
		  window.c \
		  image.c \
		  mouse.c \
		  keyboard.c

OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

# mlx library
ifeq ($(OS), Linux)
	MLXDIR	= ./miniLibX_X11
	MLX_LNK	= -l mlx -lXext -lX11
else
	MLXDIR	= ./miniLibX
	MLX_LNK	= -l mlx -framework OpenGL -framework AppKit
endif

MLX_LNK	+= -L $(MLXDIR)
MLX_INC	= -I $(MLXDIR)
MLX_LIB	= $(addprefix $(MLX)/,mlx.a)

# ft library
FTDIR	= ./libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FTDIR)

$(MLX_LIB):
	@make -C $(MLXDIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	make -C $(FT) clean
	make -C $(MLX) clean

fclean: clean
	rm $(NAME)
	make -C $(FT) fclean

re: fclean all
