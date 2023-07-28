/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:47:19 by haeem             #+#    #+#             */
/*   Updated: 2023/02/06 23:17:16 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <unistd.h>

int	ft_c_format(const char *fmt, va_list *args, t_flags *flag)
{
	int			cnt;
	const char	ch = (char)va_arg(*args, int);

	cnt = 0;
	if ((flag->num & LEFT) == false)
	{
		while (0 < --(flag->field_width))
		{
			write(STDOUT, " ", 1);
			cnt++;
		}
	}
	write(STDOUT, &ch, sizeof(char));
	cnt++;
	while (0 < --(flag->field_width))
	{
		write(1, " ", 1);
		cnt++;
	}
	return (cnt);
}
