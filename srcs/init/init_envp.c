/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:26:03 by haeem             #+#    #+#             */
/*   Updated: 2023/08/16 15:07:55 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

// save envp to hashmap for fast search
t_hashmap	*hash_envp(char **envp)
{
	t_hashmap	*newmap;
	char		**tmp;
	int			i;

	i = 0;
	newmap = hashmap_create(256);
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		hashmap_insert(newmap, tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		i++;
	}
	return (newmap);
}

// initialize envp
void	init_envp(int argc, char **argv, char **envp, t_hashmap *envmap)
{
	// int	lv;

	(void)argc;
	(void)argv;
	(void)envp;
	// (void)envmap;
	// should add PS1 and 
}
