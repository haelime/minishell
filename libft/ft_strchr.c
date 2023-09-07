/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:00:01 by haeem             #+#    #+#             */
/*   Updated: 2023/09/07 19:48:02 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// find first occurrence of ch in str and return pointer to it
// or NULL if not found
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
