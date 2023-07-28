/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:52:09 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:24:54 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void	pt(char b[], int cnt, int fd)
{
	while (cnt--)
		write(fd, &b[cnt], 1);
}

static int	counter(char b[], long long a)
{
	int	cnt;

	cnt = 0;
	while (0 < a)
	{
		b[cnt] = a % 10 + '0';
		cnt++;
		a /= 10;
	}
	return (cnt);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	a;
	char		b[11];
	int			cnt;

	cnt = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	a = n;
	if (n < 0)
	{
		a = -a;
		write(fd, "-", 1);
	}
	cnt = counter(b, a);
	pt(b, cnt, fd);
}
