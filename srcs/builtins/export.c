/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:29 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 14:20:11 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	norm_builtin_export(
					t_hashmap *envmap, char *key, char *value, int *ret)
{
	if (ft_strcmp(key, "_") == 0)
		return ;
	if (ft_strcmp(key, "") == 0)
	{
		ft_putstr_fd("minishell: export: `=", STDERR);
		ft_putstr_fd(value, STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
		free_key_value(&key, &value);
		if (*ret == SUCCESS)
			*ret = FAILURE;
		return ;
	}
	if ((!ft_isalpha(*key) && *key != '_') || is_invalid_identifier(key))
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd(key, STDERR);
		ft_putstr_fd("=': not a valid identifier\n", STDERR);
		free_key_value(&key, &value);
		if (*ret == SUCCESS)
			*ret = FAILURE;
		return ;
	}
	hashmap_insert(envmap, key, value);
	free_key_value(&key, &value);
}

static char	*export_strjoin(char *key, char *value)
{
	char	*str;
	char	*tmp;

	str = ft_strjoin("declare -x ", key);
	if (value)
	{
		tmp = ft_strjoin(str, "=\"");
		free(str);
		str = ft_strjoin(tmp, value);
		free(tmp);
		tmp = ft_strjoin(str, "\"");
		free(str);
		str = tmp;
	}
	return (str);
}

static int	sort_export(char **strs, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size)
		{
			if (ft_strcmp(strs[i], strs[j]) > 0)
			{
				tmp = strs[i];
				strs[i] = strs[j];
				strs[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	print_export(t_hashmap *hashmap)
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
			if (ft_strcmp(now->key, "?") != 0)
				*strs_p++ = export_strjoin(now->key, now->value);
			now = now->next;
		}
	}
	i = sort_export(strs, strs_p - strs);
	while (&strs[i] != strs_p)
	{
		printf("%s\n", strs[i]);
		free(strs[i++]);
	}
	free(strs);
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

	if (argv[1] == NULL)
		print_export(envmap);
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
		value = NULL;
		if (end != start)
			value = ft_substr(*argv, start + 1, end - start);
		norm_builtin_export(envmap, key, value, &ret);
	}
	return (ret);
}
