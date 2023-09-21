/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:32:12 by haeem             #+#    #+#             */
/*   Updated: 2023/09/21 18:08:29 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

void	get_input(char **p_input, t_hashmap *envmap)
{
	*p_input = NULL;
	*p_input = readline(hashmap_search(envmap, "PS1"));
	if (*p_input == NULL)
	{
		printf ("exiting minishell\n");
		exit(0);
	}
	if (ft_strlen(*p_input) == 0 || ft_isempty(*p_input))
	{
		free(*p_input);
		*p_input = NULL;
		return ;
	}
	add_history(*p_input);
}
