/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:24 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 21:16:55 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

static char	*env_strjoin(char *key, char *value)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	str = ft_strjoin(tmp, value);
	free(tmp);
	return (str);
}

static void	print_env(t_hashmap *hashmap)
{
	size_t		i;
	t_bucket	*now;
	char		**strs;
	char		**strs_p;

	strs = (char **)malloc((get_count_hashmap(hashmap)) * sizeof(char *));
	strs_p = strs;
	i = 0;
	while (i < hashmap->size)
	{
		now = hashmap->buckets[i++];
		while (now != NULL)
		{
			if (ft_strcmp(now->key, "?") != 0 && now->value != NULL)
				*strs_p++ = env_strjoin(now->key, now->value);
			now = now->next;
		}
	}
	i = 0;
	while (&strs[i] != strs_p)
	{
		printf("%s\n", strs[i]);
		free(strs[i++]);
	}
	free(strs);
}

int	builtin_env(char **argv, t_hashmap *envmap)
{
	if (argv[1] != NULL)
	{
		ft_putstr_fd("env: No such file or directory\n", STDERR_FILENO);
		return (COMMAND_NOT_FOUND);
	}
	print_env(envmap);
	return (SUCCESS);
}
