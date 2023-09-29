/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 14:03:28 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// try to remove the environment variable, if it doesn't exist, do nothing
int	builtin_unset(char **argv, t_hashmap *envmap)
{
	int	i;

	if (*(argv + 1) == NULL)
		return (SUCCESS);
	if (ft_strcmp(argv[1], "?") == 0)
		return (SUCCESS);
	while (*(++argv))
	{
		i = 0;
		if (ft_isdigit((*argv)[0]))
		{
			str_msg_ret("minishell: unset: `%s': not a valid identifier\n",
				(*argv), 0);
			return (FAILURE);
		}
		i++;
		hashmap_remove(envmap, *argv);
	}
	return (SUCCESS);
}
