/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:24:56 by haeem             #+#    #+#             */
/*   Updated: 2023/02/27 14:43:41 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_p_format(va_list	*args, t_flags *flag)
{
	unsigned long long	num;
	int					cnt;

	num = (unsigned long long)va_arg(*args, void *);
	flag->base = 16;
	flag->num |= SPECIAL;
	flag->num |= SMALL;
	flag->num &= ~SIGN;
	cnt = ft_print_num_with_flags(args, flag, num);
	return (cnt);
}
