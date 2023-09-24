/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/24 19:05:00 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// try to remove the environment variable, if it doesn't exist, do nothing
int	builtin_unset(char **argv, t_hashmap *envmap)
{
	int	i;

	if (*(argv + 1) == NULL)
		return (SUCCESS);
	while (*(++argv))
	{
		i = 0;
		while ((*argv)[i])
		{
			if (ft_isdigit((*argv)[i]))
			{
				printf ("minishell: unset: `%s': not a valid identifier\n",
					(*argv));
				return (FAILURE);
			}
			i++;
		}
		hashmap_remove(envmap, *argv);
	}
	return (SUCCESS);
}
