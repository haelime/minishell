/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 23:01:37 by haeem             #+#    #+#             */
/*   Updated: 2022/11/20 06:30:38 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *str, int ch)
{
	char	*start;

	start = (char *)str;
	while (*str++)
		;
	while (--str != start && *str != (char)ch)
		;
	if (*str == (char)ch)
		return ((char *)str);
	return (NULL);
}
