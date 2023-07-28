/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 04:58:25 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 13:28:22 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_u_format(va_list *args, t_flags *flag)
{
	const unsigned int	n = va_arg(*args, unsigned int);
	int					cnt;

	cnt = 0;
	cnt += ft_print_num_with_flags(args, flag, n);
	return (cnt);
}
