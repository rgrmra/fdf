# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 20:48:50 by rde-mour          #+#    #+#              #
#    Updated: 2024/01/13 20:35:39 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					= \033[0;91m
GREEN				= \033[0;92m
YELLOW				= \033[0;93m
BLUE				= \033[0;94m
RESET				= \033[0m

NAME = fdf

FILES = fdf.c \
		fdf_utils.c \
		fdf_parser_map.c \
		fdf_rotate.c \
		fdf_draw.c \
		fdf_color.c \
		fdf_error.c

LIBS = $(LIBFTXDIR)/libftx.a \
	   $(LIBMLXDIR)/build/libmlx42.a

SRCSDIR = ./srcs
OBJSDIR = ./objs
LIBFTXDIR = ./libs/libftx
LIBMLXDIR = ./libs/MLX42

SRCS = $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS = $(FILES:%.c=$(OBJSDIR)/%.o)

INCLUDES = -I ./includes \
		   -I ./libs/libftx/includes \
		   -I ./libs/MLX42/include/MLX42

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -ldl -lglfw -pthread -lm -Ofast

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	@$(COMPILER) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) $(INCLUDES) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(GREEN)Compiled $(RESET)$(notdir $<)"

$(LIBS):
	@git submodule sync $(LIBFTXDIR)
	@git submodule update --init --force --remote $(LIBFTXDIR)
	@make -sC $(LIBFTXDIR)
	@git submodule sync $(LIBMLXDIR)
	@git submodule update --init --force --remote $(LIBMLXDIR)
	@sed -i 's/3\.18/3.16/g' $(LIBMLXDIR)/CMakeLists.txt
	@cd $(LIBMLXDIR) && cmake -B build -DDEBUG=1 && make -sC build -j4

clean:
	@echo "$(RED)Removing $(RESET)objects"
	@make clean -sC $(LIBFTXDIR)
	@rm -Rf $(LIBMLXDIR)/build
	@rm -Rf $(OBJSDIR)

fclean: clean
	@echo "$(RED)Removing $(RESET)$(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft libmlx clean fclean re
