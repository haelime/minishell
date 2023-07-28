/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:23:40 by haeem             #+#    #+#             */
/*   Updated: 2023/02/07 03:33:36 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

static bool	ft_base_check(const char base[], int b)
{
	int	i;
	int	j;

	i = 0;
	if (b == 0 || base[0] == 0 || base[1] == 0)
		return (false);
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (false);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static int	ft_my_strlen(const char base[])
{
	int	i;

	i = 0;
	while (base[i] != '\0')
		i++;
	return (i);
}

static long long	ft_num_checker(long long num, const char base[])
{
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
		return (num);
	}
	else if (num == 0)
	{
		write (1, &base[0], 1);
		return (0);
	}
	else
		return (num);
}

int	ft_putnbr_base(const long long nbr, const char *base)
{
	int				i;
	int				base_len;
	unsigned char	buffer[500];
	long long		num;

	base_len = 0;
	num = nbr;
	base_len = ft_my_strlen(base);
	if (ft_base_check(base, base_len) == false)
		return (0);
	i = 0;
	num = ft_num_checker(num, base);
	while (num != 0)
	{
		buffer[i] = (unsigned char)base[num % base_len];
		num /= base_len;
		i++;
	}
	base_len = i;
	while (i--)
		write(1, &buffer[i], 1);
	return (base_len);
}
