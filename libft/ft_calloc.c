/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 01:12:22 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:41:03 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	*ft_calloc(size_t cnt, size_t size)
{
	void	*tmp;
	size_t	total;

	total = cnt * size;
	if (cnt != 1 && size != 1 && total == 1)
		return (NULL);
	tmp = malloc(total);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, (total));
	return (tmp);
}
