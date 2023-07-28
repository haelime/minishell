/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:08:10 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:30:24 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;

	if (to_find[0] == '\0')
		return ((char *)str);
	while (*str != '\0' && 0 < len)
	{
		i = 0;
		while (*(str + i) == *(to_find + i) && i < len)
		{
			i++;
			if (*(to_find + i) == '\0')
				return ((char *)str);
		}
		str++;
		len--;
	}
	return (0);
}
