/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:13:50 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:57:52 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"

void	ft_flag_init(t_flags *flag)
{
	flag->num = 0;
	flag->field_width = -1;
	flag->precision = -1;
	flag->base = 10;
}

void	ft_flag_setter(const char *fmt, t_flags *flag)
{
	if (*fmt == '-')
		flag->num |= LEFT;
	else if (*fmt == '+')
		flag->num |= PLUS;
	else if (*fmt == ' ')
		flag->num |= SPACE;
	else if (*fmt == '#')
		flag->num |= SHARP;
	else if (*fmt == '0')
		flag->num |= ZEROPAD;
}

int	ft_flag_handler(const char *fmt, t_flags *flag)
{
	int	cnt;

	cnt = 0;
	while (*fmt == '-' || *fmt == '+' || *fmt == '-' || *fmt == ' '
		|| *fmt == '#' || *fmt == '0')
	{
		ft_flag_setter(fmt, flag);
		cnt++;
		fmt++;
	}
	return (cnt);
}
