# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/08/24 21:04:04 by haeem            ###   ########seoul.kr   #
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
\
	./hashlib/hashmap.c\
	./hashlib/hashmap_utils.c\
\
	./init/init_shell.c\
	./init/init_envp.c\
	./init/set_env.c\
\
	./parse/get_input.c\
	./parse/minishell_parse.c\
\
	./terminal/terminal.c\
\
	./signal/signal.c\
\
	./builtins/history.c\
\
	./utils/minishell_utils.c\
)

# BONUSES = $(addprefix $(CURDIR)/srcs_bonus/,\

# )

OBJECTS = $(SOURCES:.c=.o)
BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

READLINE_FLAGS = -lreadline -L${HOME}/.brew/opt/readline/lib
READLINE_INC = -I${HOME}/.brew/opt/readline/include

# flags for github action
ACTION_READLINE = -lreadline -L/usr/local/Cellar/readline/8.2.1/lib
ACTION_READLINE_INC = -I/usr/local/Cellar/readline/8.2.1/include

HEADER = $(CURDIR)/include
BONUSHEADER = $(CURDIR)/include_bonus

ifdef WITH_BONUS
	OBJ = $(BONUSOBJECTS)
	HDR = $(BONUSHEADER)
else
	OBJ = $(OBJECTS)
	HDR = $(HEADER)
endif

ifdef ACTION
	CFLAGS = ""
endif

all: $(NAME)

bonus:
	@make WITH_BONUS=1 all

action:
	@make ACTION=1 all

%.o: %.c
	@$(CC) $(CFLAGS) $(READLINE_INC) $(ACTION_READLINE_INC) -c $< -o $@ -I $(HDR) -I $(LIBFTDIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) all
	@$(CC) $(CFLAGS) $(READLINE_FLAGS) $(ACTION_READLINE) -L$(LIBFTDIR) $(LIBFT) $^ -o $@

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