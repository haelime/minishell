/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:32:12 by haeem             #+#    #+#             */
/*   Updated: 2023/08/16 16:38:57 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

void	get_input(char *input, t_hashmap *envmap)
{
	input = readline(hashmap_search(envmap, "PS1"));
	if (input == NULL)
	{
		printf ("exiting minishell\n");
		exit(0);
	}
	if (ft_strlen(input) == 0 || ft_isempty(input))
	{
		free(input);
		return ;
	}
	add_history(input);
}
