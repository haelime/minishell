/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:35:26 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:45 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
// Iterates the list ’lst’ and applies the function ’f’ to the
// content of each element.