/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 16:06:45 by haeem             #+#    #+#             */
/*   Updated: 2023/09/24 17:48:50 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

void	set_shlvl(t_hashmap *envmap)
{
	char	*shelllvl;
	char	*value;
	int		lv;

	shelllvl = hashmap_search(envmap, "SHLVL");
	if (shelllvl == NULL)
		lv = 1;
	else
		lv = ft_atoi(shelllvl) + 1;
	value = ft_itoa(lv);
	hashmap_insert(envmap, "SHLVL", value);
	free(value);
}

void	set_ps1(t_hashmap *envmap)
{
	hashmap_insert(envmap, "PS1", "minishell$ ");
}

void	set_cwd(t_hashmap *envmap)
{
	char	*cwd;

	cwd = hashmap_search(envmap, "PWD");
	if (cwd == NULL)
	{
		cwd = getcwd(cwd, 0);
		hashmap_insert(envmap, "PWD", cwd);
		free(cwd);
	}
}

// $? Gets the status of the last command or the most recently executed process.
// $- It will print the current set of options in your current shell.
void	set_special_var(t_hashmap *envmap)
{
	hashmap_insert(envmap, "?", "0");
}

void	set_path(t_hashmap *envmap)
{
	char	*path;

	path = hashmap_search(envmap, "PATH");
	if (path == NULL)
	{
		hashmap_insert(envmap, "PATH",
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	}
}
