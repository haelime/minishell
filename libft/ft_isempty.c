/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:00:08 by haeem             #+#    #+#             */
/*   Updated: 2023/08/09 19:14:36 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"
#include <stdbool.h>

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '\v' || c == '\f' || c == '\r');
}

bool	ft_isempty(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isspace(str[i]))
			return (false);
	return (true);
}
