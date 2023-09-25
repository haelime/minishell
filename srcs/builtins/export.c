/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:29 by haeem             #+#    #+#             */
/*   Updated: 2023/09/25 20:50:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	norm_builtin_export(t_hashmap *envmap, char *key, char *value,
	int *ret)
{
	if (key == NULL)
	{
		if (*value)
		{
			free(value);
			value = NULL;
		}
		if (*ret == SUCCESS)
			*ret = FAILURE;
		return ;
	}
	if (ft_isdigit(*key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		if (*ret == SUCCESS)
			*ret = FAILURE;
		return ;
	}
	if (value == NULL)
		value = ft_strdup("");
	hashmap_insert(envmap, key, value);
	free(key);
	free(value);
}

// throws err when any *argv[0] is numeric, but works every argvs except it
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
	int		ret;

	// TODO : print_sorted_hashmap
	if (argv[1] == NULL)
		print_hashmap(envmap);
	ret = SUCCESS;
	while (*(++argv))
	{
		start = 0;
		end = 0;
		while ((*argv)[end] != '=' && (*argv)[end] != '\0')
			end++;
		key = ft_substr(*argv, start, end - start);
		start = end;
		while ((*argv)[end] != '\0')
			end++;
		value = ft_substr(*argv, start + 1, end - start);
		norm_builtin_export(envmap, key, value, &ret);
	}
	return (ret);
}
