/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 06:36:38 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:28:00 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t cnt)
{
	size_t		i;
	const char	*sp;
	char		*dp;

	if (dest == NULL && src == NULL)
		return (NULL);
	sp = src;
	dp = dest;
	i = 0;
	while (i < cnt)
	{
		*dp = *sp;
		dp++;
		sp++;
		i++;
	}
	return (dest);
}
