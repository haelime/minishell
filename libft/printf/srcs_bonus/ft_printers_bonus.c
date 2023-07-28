/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printers_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 22:55:13 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:58:17 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"
#include <unistd.h>

int	ft_print_ox(t_flags *flag)
{
	const int	locase = (flag->num & SMALL);
	int			cnt;
	char		x;

	cnt = 0;
	write(STDOUT, "0", 1);
	x = ('X' | locase);
	write(STDOUT, &x, 1);
	cnt += 2;
	return (cnt);
}

int	ft_xx_printer(t_flags *flag, char *buf)
{
	const int	locase = (flag->num & SMALL);
	int			cnt;
	char		x;

	cnt = 0;
	if (flag->num & SHARP && flag->num & NOPRINT)
		return (cnt);
	if (flag->num & SHARP)
	{
		if (flag->base == 8)
		{
			write(STDOUT, "0", 1);
			cnt++;
		}
		else if (flag->base == 16)
			cnt += ft_print_ox(flag);
	}
	if (flag->num & SPECIAL)
		cnt += ft_print_ox(flag);
	return (cnt);
}

int	ft_precision_printer(t_flags *flag, int *i)
{
	int	cnt;

	cnt = 0;
	while (*i < (flag->precision)--)
	{
		write(STDOUT, "0", 1);
		cnt++;
	}
	return (cnt);
}

int	ft_zeropad_printer(t_flags *flag)
{
	int	cnt;

	cnt = 0;
	if (!(flag->num & (ZEROPAD + LEFT)))
	{
		while (0 < (flag->field_width)--)
		{
			write(STDOUT, " ", 1);
			cnt++;
		}
	}
	return (cnt);
}

int	ft_num_printer(t_flags *flag, int *i, char *buf)
{
	int	cnt;

	cnt = 0;
	while (0 < (*i)--)
	{
		write(STDOUT, &buf[*i], 1);
		cnt++;
	}
	return (cnt);
}
