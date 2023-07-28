/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_format_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:47:19 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:58:22 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"
#include <unistd.h>

void	ft_blank_pad(t_flags *flag, int len, int *cnt)
{
	if ((flag->num & LEFT) == false)
	{
		while (len < (flag->field_width)--)
		{
			write(STDOUT, " ", 1);
			*cnt = *cnt + 1;
		}
	}
}

void	ft_blank_pad2(t_flags *flag, int len, int *cnt)
{
	if (flag->num & LEFT)
	{
		while (len < (flag->field_width)--)
		{
			write(STDOUT, " ", 1);
			*cnt = *cnt + 1;
		}
	}
}

// space, left, precision
int	ft_s_format(va_list *args, t_flags *flag)
{
	int			len;
	int			cnt;
	char		*p;
	int			i;

	cnt = 0;
	i = -1;
	p = va_arg(*args, char *);
	if (p == NULL)
		p = "(null)";
	len = ft_strnlen(p, flag->precision);
	ft_blank_pad(flag, len, &cnt);
	while (++i < len && *p != '\0')
	{
		write(STDOUT, p, 1);
		p++;
		cnt++;
	}
	ft_blank_pad2(flag, len, &cnt);
	return (cnt);
}
