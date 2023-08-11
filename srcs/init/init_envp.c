/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:26:03 by haeem             #+#    #+#             */
/*   Updated: 2023/08/11 21:00:20 by hyunjunk         ###   ########.fr       */
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
	int	lv;

	(void)argc;
	(void)argv;
	(void)envp;
	printf ("SHLVL: %s\n", hashmap_search(envmap, "SHLVL"));
	lv = ft_atoi(hashmap_search(envmap, "SHLVL")) + 1;
	printf ("SHLVL: %s\n", hashmap_search(envmap, "SHLVL"));
	hashmap_insert(envmap, "SHLVL", ft_itoa(lv));
	printf ("SHLVL: %s\n", hashmap_search(envmap, "SHLVL"));
}
