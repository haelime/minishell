/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 04:56:08 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 16:58:55 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_x_format(va_list *args, t_flags *flag)
{
	const unsigned int	n = va_arg(*args, unsigned int);
	int					cnt;

	cnt = 0;
	flag->base = 16;
	flag->num |= SMALL;
	if (n == 0 && flag->num & SHARP)
		flag->num |= NOPRINT;
	cnt += ft_print_num_with_flags(args, flag, n);
	return (cnt);
}

int	ft_xx_format(va_list *args, t_flags *flag)
{
	const unsigned int	n = va_arg(*args, unsigned int);
	int					cnt;

	cnt = 0;
	flag->base = 16;
	if (n == 0 && flag->num & SHARP)
		flag->num |= NOPRINT;
	cnt += ft_print_num_with_flags(args, flag, n);
	return (cnt);
}
