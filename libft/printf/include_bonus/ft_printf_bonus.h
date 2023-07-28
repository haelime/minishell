/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:10:08 by haeem             #+#    #+#             */
/*   Updated: 2023/02/22 18:32:37 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdarg.h>
# include <stdbool.h>
# include "./libft.h"

typedef struct s_flags
{
	int	num;
	int	field_width;
	int	precision;
	int	base;
}t_flags;

# define STDOUT		1

# define ZEROPAD	1		/* pad with zero */
# define SIGN		2		/* unsigned/signed long */
# define PLUS		4		/* show plus */
# define SPACE		8		/* space if plus */
# define LEFT		16		/* left justified */
# define SMALL		32		/* Must be 32 == 0x20 */
# define SPECIAL	64		/* 0x */
# define SHARP		128		/* # if 0 null */
# define NOPRINT	256		/* # if 0 null */

int		ft_printf(const char *fmt, ...);
int		ft_formatted_printer(const char *fmt, va_list *args);
int		ft_flag_handler(const char *fmt, t_flags *flag);
int		ft_format_handler(const char *fmt, va_list *args, int *cnt);

void	ft_flag_init(t_flags *flag);
void	ft_flag_setter(const char *fmt, t_flags *flag);

int		ft_skip_atoi(const char **s);

int		ft_get_field_width(const char *fmt, va_list *args, t_flags *flag);
int		ft_get_precision(const char *fmt, va_list *args, t_flags *flag);
void	ft_get_format(const char *fmt, va_list *args, t_flags *flag, int *cnt);

int		ft_c_format(const char *fmt, va_list *args, t_flags *flag);
int		ft_s_format(va_list *args, t_flags *flag);
int		ft_p_format(va_list	*args, t_flags *flag);
int		ft_d_format(va_list *args, t_flags *flag);
int		ft_x_format(va_list *args, t_flags *flag);
int		ft_xx_format(va_list *args, t_flags *flag);
int		ft_u_format(va_list *args, t_flags *flag);
int		ft_i_format(va_list *args, t_flags *flag);

int		ft_percent_format(t_flags *flag);

int		ft_print_num_with_flags(va_list *args, t_flags *flag, long long number);
void	ft_num_special_handler(t_flags *flag, long long *number);
char	ft_num_flag_handler(t_flags *flag, long long *number);
void	ft_num_zeropad_handler(t_flags *flag, long long *number);
int		ft_prepad_printer(t_flags *flag, int *i, char sign, char *buf);
void	ft_get_num(t_flags *flag, long long *number, char *buf, int *i);

int		ft_zeropad_printer(t_flags *flag);
int		ft_xx_printer(t_flags *flag, char *buf);
int		ft_precision_printer(t_flags *flag, int *i);
int		ft_num_printer(t_flags *flag, int *i, char *buf);
int		ft_left_printer(t_flags *flag);

#endif