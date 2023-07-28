/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:08:01 by haeem             #+#    #+#             */
/*   Updated: 2023/07/28 17:17:19 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	deque_push_back(t_deque *deque, int data)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->data = data;
	new->prev = deque->back;
	if (deque->back)
		deque->back->next = new;
	deque->back = new;
	if (!deque->front)
		deque->front = new;
	deque->size++;
}

void	deque_push_front(t_deque *deque, int data)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	new->data = data;
	new->next = deque->front;
	if (deque->front)
		deque->front->prev = new;
	deque->front = new;
	if (!deque->back)
		deque->back = new;
	deque->size++;
}

int	deque_pop_back(t_deque *deque)
{
	int		data;
	t_node	*tmp;

	if (!deque->back)
		return (0);
	data = deque->back->data;
	tmp = deque->back;
	deque->back = deque->back->prev;
	if (deque->back)
		deque->back->next = NULL;
	else
		deque->front = NULL;
	free(tmp);
	deque->size--;
	return (data);
}

int	deque_pop_front(t_deque *deque)
{
	int		data;
	t_node	*tmp;

	if (!deque->front)
		return (0);
	data = deque->front->data;
	tmp = deque->front;
	deque->front = deque->front->next;
	if (deque->front)
		deque->front->prev = NULL;
	else
		deque->back = NULL;
	free(tmp);
	deque->size--;
	return (data);
}
