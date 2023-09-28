/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:32:12 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 19:25:04 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

void	get_input(char **p_input)
{
	if (*p_input)
		free(*p_input);
	*p_input = NULL;
	*p_input = readline("minishell$ ");
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
