/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 03:15:41 by haeem             #+#    #+#             */
/*   Updated: 2023/02/12 17:31:22 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_d_format(va_list *args, t_flags *flag)
{
	int			cnt;
	const int	n = va_arg(*args, int);

	cnt = 0;
	cnt += ft_print_num_with_flags(args, flag, n);
	return (cnt);
}
