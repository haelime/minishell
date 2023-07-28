/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 03:23:35 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:36 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = ft_strdup(s);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		str[i] = f(i, str[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
// Applies the function ’f’ to each character of the string ’s’ ,
// and passing its index as first argument to
// create a new string (with malloc(3))
// resulting from successive applications of ’f’.