# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 13:40:12 by haeem             #+#    #+#              #
#    Updated: 2023/09/07 19:39:14 by haeem            ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = $(CURDIR)

NAME = libft.a
LIBFT = $(SRCDIR)/libft.a
HEADER = $(CURDIR)/include

SOURCES = ft_strlen.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_strchr.c\
ft_strnstr.c\
ft_strcmp.c\
ft_strncmp.c\
ft_strdup.c\
ft_strrchr.c\
ft_memset.c\
ft_memcpy.c\
ft_memmove.c\
ft_memchr.c\
ft_memcmp.c\
ft_bzero.c\
ft_atoi.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_isquote.c\
ft_strdup.c\
ft_tolower.c\
ft_toupper.c\
ft_substr.c\
ft_strreplace.c\
ft_strjoin.c\
ft_strtrim.c\
ft_split.c\
ft_strmapi.c\
ft_striteri.c\
ft_itoa.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putnbr_base.c\
ft_lstnew_bonus.c\
ft_lstsize_bonus.c\
ft_lstadd_front_bonus.c\
ft_lstadd_back_bonus.c\
ft_lstclear_bonus.c\
ft_lstlast_bonus.c\
ft_lstiter_bonus.c\
ft_lstmap_bonus.c\
ft_lstdelone_bonus.c\
ft_minmax.c\
ft_swap.c\
ft_selection_sort.c\
ft_binary_search.c\
ft_isempty.c\
./get_next_line/get_next_line_bonus.c\
./get_next_line/get_next_line_utils_bonus.c\
./printf/srcs_bonus/ft_printf_bonus.c\
./printf/srcs_bonus/ft_flag_handler_bonus.c\
./printf/srcs_bonus/ft_num_processor_bonus.c\
./printf/srcs_bonus/ft_get_format_bonus.c\
./printf/srcs_bonus/ft_get_precision_bonus.c\
./printf/srcs_bonus/ft_get_width_bonus.c\
./printf/srcs_bonus/ft_printers_bonus.c\
./printf/srcs_bonus/ft_c_format_bonus.c\
./printf/srcs_bonus/ft_s_format_bonus.c\
./printf/srcs_bonus/ft_d_format_bonus.c\
./printf/srcs_bonus/ft_p_format_bonus.c\
./printf/srcs_bonus/ft_x_format_bonus.c\
./printf/srcs_bonus/ft_u_format_bonus.c\
./printf/srcs_bonus/ft_percent_format_bonus.c\
./printf/srcs_bonus/ft_print_num_with_flags_bonus.c\
./deque/deque.c\
./deque/deque2.c\
./deque/deque3.c\


OBJECTS = $(SOURCES:.c=.o)

all: $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAG) -c $< -o $@ -I $(CURDIR)/$(HEADER)

$(LIBFT): $(OBJECTS)
	@ar crs $@ $^

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(LIBFT)

re: fclean all

.PHONY: re clean fclean all