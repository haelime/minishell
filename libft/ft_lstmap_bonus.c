/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:37:50 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:44 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	void	*newcontent;
	t_list	*newnode;

	newlist = NULL;
	while (lst != NULL)
	{
		newcontent = f(lst->content);
		newnode = ft_lstnew(newcontent);
		if (newnode == NULL)
		{
			del(newcontent);
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}
// Iterates the list ’lst’ and applies the function ’f’
// to the content of each element.
// Creates a new list resulting of the successive applications
// of the function ’f’.
// The ’del’ function is used to delete the content of an element if needed.
