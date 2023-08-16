# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/08/16 15:13:42 by haeem            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3\
# -g -fsanitize=address
SRCDIR = $(CURDIR)

NAME = minishell

LIBFTDIR = $(SRCDIR)/libft
LIBFT = ./libft/libft.a
LIBFTHEADER = ./libft/include/libft.h

SOURCES = $(addprefix $(CURDIR)/srcs/,\
	minishell_main.c\
	./hashlib/hashmap.c\
	./hashlib/hashmap_utils.c\
	./init/init_shell.c\
	./init/init_envp.c\
	./parse/minishell_parse.c\
	./terminal/terminal.c\
	./signal/signal.c\
)

# BONUSES = $(addprefix $(CURDIR)/srcs_bonus/,\

# )

OBJECTS = $(SOURCES:.c=.o)
BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

COMFILE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
OBJ_FLAGS = -I${HOME}/.brew/opt/readline/include

# flags for github action
ACTION_FLAGS = -lreadline -L/usr/local/Cellar/readline/8.2.1/lib
ACTION_OBJ_FLAGS = -I/usr/local/Cellar/readline/8.2.1/include

HEADER = $(CURDIR)/include
BONUSHEADER = $(CURDIR)/include_bonus

ifdef WITH_BONUS
	OBJ = $(BONUSOBJECTS)
	HDR = $(BONUSHEADER)
else
	OBJ = $(OBJECTS)
	HDR = $(HEADER)
endif

all: $(NAME)

bonus:
	@make WITH_BONUS=1 all

action: $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) all
	@$(CC) $(ACTION_FLAGS) -L$(LIBFTDIR) $(LIBFT) $^ -o $@

%.o: %.c
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) $(ACTION_OBJ_FLAGS) -c $< -o $@ -I $(HDR) -I $(LIBFTDIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) all
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) $(ACTION_FLAGS) -L$(LIBFTDIR) $(LIBFT) $^ -o $@

clean:
	@rm -f $(ALLOBJECTS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

libft:
	@make -C $(LIBFTDIR) all

re: fclean all

.PHONY: re clean fclean all bonus libft