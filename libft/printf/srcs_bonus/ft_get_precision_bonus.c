/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_precision_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:09:50 by haeem             #+#    #+#             */
/*   Updated: 2023/02/22 18:56:34 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"

int	ft_precision(const char *fmt, t_flags *flag, int *cnt, int *tmp)
{
	int	i;

	i = 0;
	while (*fmt == '0')
	{
		fmt++;
		*cnt = *cnt + 1;
		i++;
	}
	flag->precision = ft_skip_atoi(&fmt);
	*tmp = flag->precision;
	while (*tmp != 0)
	{
		*tmp /= 10;
		*cnt = *cnt + 1;
		i++;
	}
	return (i);
}

int	ft_get_precision(const char *fmt, va_list *args, t_flags *flag)
{
	int	cnt;
	int	tmp;

	cnt = 0;
	if (*fmt++ == '.')
	{
		cnt++;
		if (ft_isdigit(*fmt))
		{
			fmt += ft_precision(fmt, flag, &cnt, &tmp);
			return (cnt);
		}
		if (flag->precision < 0)
			flag->precision = 0;
	}
	return (cnt);
}
