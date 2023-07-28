/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:00:01 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:28:46 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int ch)
{
	while (*str != (char)ch)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}
