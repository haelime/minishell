# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 22:11:16 by haeem             #+#    #+#              #
#    Updated: 2023/03/15 17:56:47 by haeem            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar -crus
SRCDIR = $(CURDIR)

NAME = libftprintf.a
LIBFTDIR = ../../libft
LIBFT = ../libft.a
LIBFTHEADER = ../libft.h

SOURCES = ./srcs/ft_printf.c\
./srcs/ft_flag_handler.c\
./srcs/ft_num_processor.c\
./srcs/ft_get_format.c\
./srcs/ft_get_precision.c\
./srcs/ft_get_width.c\
./srcs/ft_printers.c\
./srcs/ft_c_format.c\
./srcs/ft_s_format.c\
./srcs/ft_d_format.c\
./srcs/ft_p_format.c\
./srcs/ft_x_format.c\
./srcs/ft_u_format.c\
./srcs/ft_percent_format.c\
./srcs/ft_print_num_with_flags.c\

BONUSES = ./srcs_bonus/ft_printf_bonus.c\
./srcs_bonus/ft_flag_handler_bonus.c\
./srcs_bonus/ft_num_processor_bonus.c\
./srcs_bonus/ft_get_format_bonus.c\
./srcs_bonus/ft_get_precision_bonus.c\
./srcs_bonus/ft_get_width_bonus.c\
./srcs_bonus/ft_printers_bonus.c\
./srcs_bonus/ft_c_format_bonus.c\
./srcs_bonus/ft_s_format_bonus.c\
./srcs_bonus/ft_d_format_bonus.c\
./srcs_bonus/ft_p_format_bonus.c\
./srcs_bonus/ft_x_format_bonus.c\
./srcs_bonus/ft_u_format_bonus.c\
./srcs_bonus/ft_percent_format_bonus.c\
./srcs_bonus/ft_print_num_with_flags_bonus.c\

OBJECTS = $(SOURCES:.c=.o)
BONUSOBJECTS = $(BONUSES:.c=.o)
ALLOBJECTS = $(SOURCES:.c=.o) $(BONUSES:.c=.o)

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
	make WITH_BONUS=1 all

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@ -I $(HDR)

$(NAME): $(OBJ) $(LIBFT)
	@cp ../libft.a $(SRCDIR)/$(NAME)
	@ar crus $@ $(OBJ)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR) all

clean:
	@rm -f $(ALLOBJECTS)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: re clean fclean all bonus libft