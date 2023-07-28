/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num_with_flags.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 20:30:41 by haeem             #+#    #+#             */
/*   Updated: 2023/02/22 19:22:11 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include <unistd.h>

void	ft_get_ull(t_flags *flag, int *i, char *buf,
		unsigned long long *number)
{
	const int	lower = (flag->num & SMALL);
	const char	base[16] = "0123456789ABCDEF";

	buf[(*i)++] = (base[(unsigned long long)*number
			% (unsigned)flag->base] | lower);
	*number /= flag->base;
	while (*number != 0)
	{
		buf[(*i)++] = (base[(unsigned long long)*number
				% (unsigned)flag->base] | lower);
		*number /= flag->base;
	}
}

void	ft_get_num(t_flags *flag, long long *number, char *buf, int *i)
{
	const int			lower = (flag->num & SMALL);
	const char			base[16] = "0123456789ABCDEF";

	if (flag->precision == 0 && *number == 0)
		return ;
	if (flag->num & SPECIAL && *number < 0)
	{
		ft_get_ull(flag, i, buf, (unsigned long long *) number);
		return ;
	}
	if (*number < 0)
		*number = -(*number);
	buf[(*i)++] = (base[(unsigned long long)*number
			% (unsigned)flag->base] | lower);
	*number /= flag->base;
	while (*number != 0)
	{
		buf[(*i)++] = (base[(unsigned long long)*number
				% (unsigned)flag->base] | lower);
		*number /= flag->base;
	}
}

int	ft_left_printer(t_flags *flag)
{
	int	cnt;
	int	c;

	cnt = 0;
	if (flag->num & ZEROPAD)
		c = '0';
	else
		c = ' ';
	if (!(flag->num & LEFT))
	{
		while (0 < (flag->field_width)--)
		{
			write(STDOUT, &c, 1);
			cnt++;
		}
	}
	return (cnt);
}

int	ft_prepad_printer(t_flags *flag, int *i, char sign, char *buf)
{
	int	cnt;

	cnt = 0;
	if (flag->precision < *i)
		flag->precision = *i;
	flag->field_width -= flag->precision;
	cnt += ft_zeropad_printer(flag);
	cnt += ft_xx_printer(flag, buf);
	if (sign)
	{
		write(STDOUT, &sign, 1);
		cnt++;
	}
	cnt += ft_left_printer(flag);
	cnt += ft_precision_printer(flag, i);
	cnt += ft_num_printer(flag, i, buf);
	return (cnt);
}

int	ft_print_num_with_flags(va_list *args, t_flags *flag, long long number)
{
	char	buf[18];
	int		cnt;
	int		i;
	char	sign;

	i = 0;
	cnt = 0;
	sign = ft_num_flag_handler(flag, &number);
	ft_get_num(flag, &number, buf, &i);
	cnt += ft_prepad_printer(flag, &i, sign, buf);
	ft_num_printer(flag, &i, buf);
	while (0 < (flag->field_width)--)
	{
		write(STDOUT, " ", 1);
		cnt++;
	}
	return (cnt);
}
