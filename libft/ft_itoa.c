/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 02:50:22 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:37:57 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

size_t	ft_get_decimal_length(const int nb)
{
	int	len;
	int	num;

	len = 0;
	num = nb;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*str;
	long	num;

	len = ft_get_decimal_length(n);
	num = n;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (num != 0)
	{
		str[len] = num % 10 + '0';
		len--;
		num = num / 10;
	}
	return (str);
}
