/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:17:28 by haeem             #+#    #+#             */
/*   Updated: 2023/02/27 14:44:16 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

void	ft_get_format(const char *fmt, va_list *args, t_flags *flag, int *cnt)
{
	if (*fmt == 'c')
		*cnt += ft_c_format(fmt, args, flag);
	else if (*fmt == 's')
		*cnt += ft_s_format(args, flag);
	else if (*fmt == 'p')
		*cnt += ft_p_format(args, flag);
	else if (*fmt == '%')
		*cnt += ft_percent_format(flag);
	else if (*fmt == 'x')
		*cnt += ft_x_format(args, flag);
	else if (*fmt == 'X')
		*cnt += ft_xx_format(args, flag);
	else if (*fmt == 'd')
		*cnt += ft_d_format(args, flag);
	else if (*fmt == 'i')
		*cnt += ft_d_format(args, flag);
	else if (*fmt == 'u')
		*cnt += ft_u_format(args, flag);
}
