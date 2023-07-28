/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 18:01:00 by haeem             #+#    #+#             */
/*   Updated: 2023/02/07 04:12:12 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_skip_atoi(const char **s)
{
	int	i;

	i = 0;
	while (ft_isdigit((int)**s))
	{	
		i = i * 10 + *((*s)++) - '0';
	}
	return (i);
}

int	ft_get_field_width(const char *fmt, va_list *args, t_flags *flag)
{
	int	cnt;
	int	tmp;

	cnt = 0;
	if (ft_isdigit((int)*fmt))
	{
		while (*fmt == '0')
		{
			fmt++;
			cnt++;
		}
		flag->field_width = ft_skip_atoi(&fmt);
		tmp = flag->field_width;
		while (tmp != 0)
		{
			tmp /= 10;
			cnt++;
		}
		return (cnt);
	}
	return (cnt);
}
