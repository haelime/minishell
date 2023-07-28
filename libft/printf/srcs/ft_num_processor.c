/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_processor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:57:29 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:29:30 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <unistd.h>

void	ft_num_zeropad_handler(t_flags *flag, long long *number)
{
	if (flag->num & LEFT)
		flag->num &= ~ZEROPAD;
	if (flag->precision != -1)
		flag->num &= ~ZEROPAD;
}

void	ft_num_special_handler(t_flags *flag, long long *number)
{
	if (flag->num & SHARP)
	{
		if (*number == 0)
			return ;
		if (flag->base == 16)
			flag->field_width -= 2;
		else if (flag->base == 8)
			(flag->field_width)--;
	}
	else if (flag->num & SPECIAL)
	{
		if (flag->base == 16)
			flag->field_width -= 2;
		else if (flag->base == 8)
			(flag->field_width)--;
	}
}

char	ft_num_sign_handler(t_flags *flag, long long *num)
{
	char	sign;

	sign = 0;
	if (*num < 0 && !(flag->num & SPECIAL))
	{
		sign = '-';
		*num = -(*num);
		flag->field_width--;
	}
	else if (flag->num & PLUS)
	{
		sign = '+';
		flag->field_width--;
	}
	else if (flag->num & SPACE)
	{
		sign = ' ';
		flag->field_width--;
	}
	return (sign);
}

char	ft_num_flag_handler(t_flags *flag, long long *number)
{
	const char	sign = ft_num_sign_handler(flag, number);

	ft_num_zeropad_handler(flag, number);
	ft_num_special_handler(flag, number);
	return (sign);
}
