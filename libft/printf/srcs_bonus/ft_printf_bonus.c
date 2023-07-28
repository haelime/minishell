/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:03:22 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:58:19 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"
#include <unistd.h>

int	ft_format_handler(const char *fmt, va_list *args, int *cnt)
{
	t_flags		flag;
	const char	*p;

	ft_flag_init(&flag);
	p = fmt;
	fmt += ft_flag_handler(fmt, &flag);
	fmt += ft_get_field_width(fmt, args, &flag);
	fmt += ft_get_precision(fmt, args, &flag);
	ft_get_format(fmt, args, &flag, cnt);
	return (fmt - p);
}

int	ft_formatted_printer(const char *fmt, va_list *args)
{
	int	cnt;

	cnt = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			fmt += ft_format_handler(fmt, args, &cnt);
		}
		else
		{
			write(STDOUT, fmt, sizeof(char));
			cnt++;
		}
		fmt++;
	}
	return (cnt);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		printed;

	va_start(args, fmt);
	printed = ft_formatted_printer(fmt, &args);
	va_end(args);
	return (printed);
}
