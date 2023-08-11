# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 14:22:09 by haeem             #+#    #+#              #
#    Updated: 2023/08/11 20:45:19 by hyunjunk         ###   ########.fr        #
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

%.o: %.c
	@$(CC) $(CFLAGS) $(OBJ_FLAGS) -c $< -o $@ -I $(HDR) -I $(LIBFTDIR)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFTDIR) all
	@$(CC) $(CFLAGS) $(COMFILE_FLAGS) -L$(LIBFTDIR) $(LIBFT) $^ -o $@

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