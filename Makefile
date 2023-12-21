# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 20:48:50 by rde-mour          #+#    #+#              #
#    Updated: 2023/12/21 20:46:08 by rde-mour         ###   ########.org.br    #
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

LIBS = $(LIBFTDIR)/libft.a \
	   $(LIBMLXDIR)/build/libmlx42.a $(MLXFLAGS)

SRCSDIR = ./srcs
OBJSDIR = ./objs
LIBFTDIR = ./libs/libft
LIBMLXDIR = ./libs/MLX42

SRCS = $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS = $(FILES:%.c=$(OBJSDIR)/%.o)

INCLUDES = -I ./includes -D ROTATION=0.001 \
		   -I ./libs/libft/includes \
		   -I ./libs/MLX42/includes

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -ldl -lglfw -pthread -lm

M :=

ifndef MAP
	MAP = ./maps/42.fdf
else
	MPA = M
endif

all: libft libmlx $(NAME)

$(NAME): $(OBJS)
	@$(COMPILER) $(CFLAGS) -Ofast $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)

e: all
	valgrind --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./fdf $(MAP)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "$(GREEN)Compiled $(RESET)$(notdir $<)"

libft:
	@make -sC $(LIBFTDIR)

libmlx:
	@git submodule sync
	@git submodule init
	@git submodule update
	@cd $(LIBMLXDIR) && cmake -B build -DDEBUG=1 && make -sC build -j4

clean:
	@echo "$(RED)Removing $(RESET)objects"
	@make clean -sC $(LIBFTDIR)
	@rm -Rf $(LIBMLXDIR)/build
	@rm -Rf $(OBJSDIR)

fclean: clean
	@make fclean -sC $(LIBFTDIR)
	@echo "$(RED)Removing $(RESET)$(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all libft libmlx clean fclean re

