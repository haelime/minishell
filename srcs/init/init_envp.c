/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:26:03 by haeem             #+#    #+#             */
/*   Updated: 2023/09/17 17:16:02 by haeem            ###   ########seoul.kr  */
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
	char		**p;

	i = 0;
	newmap = hashmap_create(256);
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (tmp[1] == NULL)
			hashmap_insert(newmap, tmp[0], "");
		else
			hashmap_insert(newmap, tmp[0], tmp[1]);
		p = tmp;
		while (*p != NULL)
			free(*p++);
		free(tmp);
		i++;
	}
	return (newmap);
}

// initialize envp
void	init_envp(int argc, char **argv, char **envp, t_hashmap *envmap)
{
	(void)envp;
	(void)argc;
	(void)argv;
	set_shlvl(envmap);
	set_ps1(envmap);
	set_cwd(envmap);
	set_special_var(envmap);
	set_path(envmap);
}
