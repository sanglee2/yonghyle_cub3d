# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/13 11:43:23 by jrameau           #+#    #+#              #
#    Updated: 2023/10/08 12:09:04 by sanglee2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCDIR			=	./src/
SRCNAMES		=	$(shell ls $(SRCDIR) | grep -E ".+\.c")
SRC				=	$(addprefix $(SRCDIR), $(SRCNAMES))
INC				=	-I./inc/ -I./mlx/
BUILDDIR		=	./build/
BUILDOBJS		=	$(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))
SUBDIRS			=	./mlx	

MLX 			=   ./mlx/libmlx.a
MLXDIR 			= 	./mlx
MLXFLAG			=	-Lmlx -lmlx -framework OpenGL -framework AppKit

CC				=	cc
CFLAGS			=	-Wall -Werror -Wextra

all				:	$(BUILDDIR) $(NAME)

$(BUILDDIR)		:
					mkdir -p $(BUILDDIR)

$(BUILDDIR)%.o	:	$(SRCDIR)%.c
					$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NAME)			: 	$(BUILDOBJS) $(MLX) ./inc/cub3d.h ./map.cub
					$(CC) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(MLXFLAG)

$(MLX)			:
					$(MAKE) -C $(MLXDIR)

clean			:	$(SUBDIRS)
					rm -rf $(BUILDDIR)
					@echo "Cleaning in subdirectories"
					@for dir in $(SUBDIRS); do \
    					$(MAKE) -C $$dir clean; \
    				done

fclean			:	clean
					rm -rf $(NAME)

re				:	fclean all

.PHONY			:	all fclean clean re
