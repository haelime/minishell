# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/09/21 16:25:03 by hyunjunk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror -g3\
# -fsanitize=address
SRCDIR = $(CURDIR)

NAME = minishell

LIBFTDIR = $(SRCDIR)/libft
LIBFT = ./libft/libft.a
LIBFTHEADER = ./libft/include/libft.h

SOURCES = $(addprefix $(SRCDIR)/srcs/,\
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
	./parse/tokenize.c\
	./parse/parse_utils.c\
	./parse/command_block.c\
	./parse/syntax_word.c\
	./parse/check_parse_invalid.c\
\
	./execute/execute.c\
	./execute/execute_utils.c\
	./execute/find_completed_cmd.c\
\
	./terminal/terminal.c\
\
	./signal/signal.c\
\
	./utils/minishell_utils.c\
\
	./builtins/env.c\
	./builtins/pwd.c\
	./builtins/unset.c\
	./builtins/echo.c\
)

# BONUSES = $(addprefix $(CURDIR)/srcs_bonus/,\

# )

OBJECTS = $(SOURCES:.c=.o)
BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

READLINE_FLAGS = -lreadline -L/usr/local/lib
READLINE_INC = -I/usr/local/include/readline

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
	@$(CC) $(CFLAGS) $(READLINE_FLAGS) $(ACTION_READLINE) $^ -o $@ -L$(LIBFTDIR) $(LIBFT)

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