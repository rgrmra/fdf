# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/26 20:48:50 by rde-mour          #+#    #+#              #
#    Updated: 2024/01/16 22:02:44 by rde-mour         ###   ########.org.br    #
#                                                                              #
# **************************************************************************** #

RED					= $(shell tput setaf 1)
GREEN				= $(shell tput setaf 2)
YELLOW				= $(shell tput setaf 3)
BLUE				= $(shell tput setaf 4)
MAGENT				= $(shell tput setaf 5)
RESET				= $(shell tput sgr0)

NAME = fdf

FILES = fdf.c \
		fdf_utils.c \
		fdf_parser_map.c \
		fdf_rotate.c \
		fdf_draw.c \
		fdf_keys.c \
		fdf_error.c

LIBS = $(LIBFTXDIR)/libftx.a \
	   $(LIBMLXDIR)/build/libmlx42.a

SRCSDIR = ./srcs
OBJSDIR = ./objs
LIBFTXDIR = ./libs/libftx
LIBMLXDIR = ./libs/MLX42

SRCS = $(FILES:%.c=$(SRCSDIR)/%.c)
OBJS = $(FILES:%.c=$(OBJSDIR)/%.o)
SRCS_BONUS = $(FILES:%.c=$(SRCSDIR)/bonus/%_bonus.c)
OBJS_BONUS = $(FILES:%.c=$(OBJSDIR)/bonus/%_bonus.o)

MESSAGE = mandatory
DELETE = $(OBJS_BONUS)

INCLUDES = -I ./includes \
		   -I ./libs/libftx/includes \
		   -I ./libs/MLX42/include/MLX42

COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g3
MLXFLAGS = -ldl -lglfw -pthread -lm -Ofast

ifdef	WITH_BONUS
	DELETE := $(OBJS)
	SRCS := $(SRCS_BONUS)
	OBJS := $(OBJS_BONUS)
	MESSAGE := bonus
endif

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	@rm -Rf $(DELETE)
	@$(COMPILER) $(CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) $(INCLUDES) -o $(NAME)
	@echo "$(BLUE)Compiled $(NAME) $(MESSAGE) successfully$(RESET)"

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

bonus:
	@make WITH_BONUS=TRUE --no-print-directory

clean:
	@echo "$(RED)Removing $(RESET)objects"
	@rm -Rf $(OBJSDIR)

fclean: clean
	@echo "$(RED)Removing $(RESET)$(NAME)"
	@make fclean -sC $(LIBFTXDIR)
	@rm -Rf $(LIBMLXDIR)/build
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
