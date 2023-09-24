/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:29 by haeem             #+#    #+#             */
/*   Updated: 2023/09/24 17:17:29 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	norm_builtin_export(t_hashmap *envmap, char *key, char *value)
{
	if (key == NULL)
		return (BUILTIN);
	if (value == NULL)
		value = ft_strdup("");
	hashmap_insert(envmap, key, value);
	free(key);
	free(value);
	return (SUCCESS);
}

// syntax is already checked & replaced dollar, so trust every argv
//   end
//    |
// zzz=asdf           get key "zzz"
// ^
// start
// -------------------------------------------------------------------
//   end
//    |
// zzz=asdf           move start to first found "="
//    ^
//  start
// -------------------------------------------------------------------
//        end
//         |
// zzz=asdf           get value "asdf"
//    ^
//  start
int	builtin_export(char **argv, t_hashmap *envmap)
{
	int		start;
	int		end;
	char	*key;
	char	*value;

	if (argv[1] == NULL)
	{
		print_hashmap(envmap);
		key = NULL;
	}
	while (*(++argv))
	{
		start = 0;
		end = 0;
		while ((*argv)[end] != '=' && (*argv)[end] != '\0')
			end++;
		if ((*argv)[end] == '\0')
			return (SUCCESS);
		key = ft_substr(*argv, start, end - start);
		start = end;
		while ((*argv)[end] != '\0')
			end++;
		value = ft_substr(*argv, start, end - start);
	}
	return (norm_builtin_export(envmap, key, value));
}
