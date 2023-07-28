/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_format_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:47:19 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:57:25 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"
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
