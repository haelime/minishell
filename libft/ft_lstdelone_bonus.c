/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:18:26 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:46 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
// Takes as a parameter an element and frees the memory of the element’s 
// content using the function ’del’
// given as a parameter and free the element.
// The memory of ’next’ must not be freed.