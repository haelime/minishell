/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:01:16 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newlist)
{
	t_list	*tmp;

	if (newlist == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = newlist;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	(*lst)->next = newlist;
	*lst = tmp;
}
// Adds the element ’new’ at the end of the list.