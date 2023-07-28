/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:15:53 by haeem             #+#    #+#             */
/*   Updated: 2023/07/28 17:17:30 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	deque_is_empty(t_deque *deque)
{
	return (deque->size == 0);
}

int	deque_size(t_deque *deque)
{
	return (deque->size);
}

int	deque_front(t_deque *deque)
{
	if (deque_is_empty(deque))
		return (0);
	return (deque->front->data);
}

int	deque_back(t_deque *deque)
{
	if (deque_is_empty(deque))
		return (0);
	return (deque->back->data);
}
