/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent_format_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:45:04 by haeem             #+#    #+#             */
/*   Updated: 2023/02/16 18:58:13 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/ft_printf_bonus.h"
#include <unistd.h>

int	ft_percent_format(t_flags *flag)
{
	int	cnt;

	cnt = 0;
	if ((flag->num & LEFT) == false)
	{
		while (0 < --(flag->field_width))
		{
			write(STDOUT, " ", 1);
			cnt++;
		}
	}
	write(1, "%", 1);
	cnt++;
	while (0 < --(flag->field_width))
	{
		write(1, " ", 1);
		cnt++;
	}
	return (cnt);
}
