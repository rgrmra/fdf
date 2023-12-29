# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 20:48:50 by rde-mour          #+#    #+#              #
#    Updated: 2023/12/28 21:41:53 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					= \033[0;91m
GREEN				= \033[0;92m
YELLOW				= \033[0;93m
BLUE				= \033[0;94m
RESET				= \033[0m

NAME = fdf

FILES = main.c \
		fdf_utils.c \
		fdf_parser_map.c \
		fdf_rotate.c \
		fdf_draw.c

LIBS = $(LIBFTXDIR)/libftx.a \
	   $(LIBMLXDIR)/build/libmlx42.a $(MLXFLAGS)

SRCSDIR = ./srcs
OBJSDIR = ./objs
LIBFTXDIR = ./libs/libftx
LIBMLXDIR = ./libs/MLX42

SRCS = $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS = $(FILES:%.c=$(OBJSDIR)/%.o)

INCLUDES = -I ./includes -D ROTATION=0.001 \
		   -I ./libs/libftx/includes \
		   -I ./libs/MLX42/includes

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -ldl -lglfw -pthread -lm

all: libftx libmlx $(NAME)

$(NAME): $(OBJS)
	@$(COMPILER) $(CFLAGS) -Ofast $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo -e "$(GREEN)Compiled $(RESET)$(notdir $<)"

libftx:
	@git submodule sync $(LIBFTXDIR)
	@git submodule update --init --force --remote $(LIBFTXDIR)
	@make -sC $(LIBFTXDIR)

libmlx:
	@git submodule sync $(LIBMLXDIR)
	@git submodule update --init --force --remote $(LIBMLXDIR)
	@cd $(LIBMLXDIR) && cmake -B build -DDEBUG=1 && make -sC build -j4

clean:
	@echo -e "$(RED)Removing $(RESET)objects"
	@make clean -sC $(LIBFTXDIR)
	@rm -Rf $(LIBMLXDIR)/build
	@rm -Rf $(OBJSDIR)

fclean: clean
	@echo -e "$(RED)Removing $(RESET)$(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft libmlx clean fclean re

