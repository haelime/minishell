/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:30:05 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:27:10 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *p, int value, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		if (((unsigned char *)p)[i] == (unsigned char)value)
			return ((void *)p + i);
		i++;
	}
	return ((void *)0);
}
