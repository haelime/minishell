/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:38:08 by haeem             #+#    #+#             */
/*   Updated: 2023/09/07 20:54:40 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strreplace(char *str, char *old, char *new)
{
	char	*temp;
	char	*temp2;
	char	*result;
	int		len;

	if (!str || !old)
		return ((void *)0);
	temp = ft_strnstr(str, old, ft_strlen(str));
	if (!temp)
		return (str);
	if (!new)
		return (ft_strreplace(str, old, "\0"));
	len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new);
	result = (char *)malloc(sizeof(char) * (len + 1));
	temp2 = result;
	while (str != temp)
		*temp2++ = *str++;
	while (*new)
		*temp2++ = *new++;
	str += ft_strlen(old);
	while (*str)
		*temp2++ = *str++;
	*temp2 = '\0';
	return (result);
}
