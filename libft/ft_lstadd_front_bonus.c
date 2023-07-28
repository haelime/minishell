/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:34:49 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *newlist)
{
	if (lst == NULL || newlist == NULL)
		return ;
	newlist->next = *lst;
	*lst = newlist;
}
// Adds the element ’new’ at the beginning of the list.