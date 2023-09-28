/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:32 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 22:44:33 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// prints working directory
int	builtin_pwd(t_hashmap *hashmap)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		path = hashmap_search(hashmap, "PWD");
		if (path == NULL)
			return (BUILTIN);
		printf("%s\n", path);
		return (SUCCESS);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}
