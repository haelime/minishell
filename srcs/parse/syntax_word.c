/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:50:18 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 18:58:16 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

// make key, from $ to null, $ or ' '
char	*make_key(char **o_str, char **o_start, char **o_end)
{
	char	*key;

	(*o_end)++;
	if (**o_end == '$')
		return (ft_strdup("$$"));
	// if (str[j] == '?')
		// return (g_exitnum);
	while (**o_start != '$')
		(*o_start)++;
	while (**o_end && **o_end != ' ' && **o_end != '$' && **o_end != '\"'
		&& **o_end != '\'' && **o_end != '>' && **o_end != '<' && **o_end != '|'
		&& **o_end != '/' && **o_end != '\\')
		(*o_end)++;
	key = ft_substr(*o_str, *o_start - *o_str + 1, *o_end - *o_start - 1);
	*o_start = *o_end;
	return (key);
}

void	join_value_before_it(char **o_ret, char **o_str, char **o_start, char **o_end)
{
	char	*key_before;

	key_before = ft_substr(*o_str, *o_start - *o_str, *o_end - *o_start);
	*o_ret = ft_strjoinfree(o_ret, &key_before);
	*o_start = *o_end;
}

char	*join_remain(char **o_ret, char **o_str, char **o_start, char **o_end)
{
	char	*remain;
	char	*ret;

	remain = ft_substr(*o_str, *o_start - *o_str, *o_end - *o_str);
	if (*remain == '\0')
	{
		free(remain);
		return (*o_ret);
	}
	if (*o_ret != NULL)
	{
		ret = ft_strjoinfree(o_ret, &remain);
		return (ret);
	}
	else
		return (remain);
}

char	*get_value(
		char **o_str, char **o_start, char **o_end, t_hashmap *envmap)
{
	char	*key;
	char	*value;
	char	*tmp;


	key = make_key(o_str, o_start, o_end);
	if (*key == '\0')
	{
		free(key);
		return (ft_strdup("$"));
	}
	tmp = hashmap_search(envmap, key);
	if (tmp == NULL)
	{
		free(key);
		tmp = ft_strdup("");
		return (tmp);
	}
	else
	{
		free(key);
		value = ft_strdup(tmp);
		return (value);
	}
}

// TODO

// dollar to env if not quoted
// @Arguments	is_heredoc_mode
//						IF (0) 	THEN (ignore '$' in ''')
char	*replace_dollar(char *str, t_hashmap *envmap)
{
	char	*start;
	char	*end;
	int		flag;
	char	*ret;
	char	*value;

	flag = 0;
	start = str;
	end = start;
	ret = ft_strdup("");
	while (*end)
	{
		if (*end == '\'' && !(flag & DOUBLEQUOTE))
			flag ^= QUOTE;
		if (*end == '\"' && !(flag & QUOTE))
			flag ^= DOUBLEQUOTE;
		if (*end == '$' && (flag == 0 || flag & DOUBLEQUOTE))
		{
			join_value_before_it(&ret, &str, &start, &end);
			value = get_value(&str, &start, &end, envmap);
			ret = ft_strjoinfree(&ret, &value);
			end--;
		}
		end++;
	}
	ret = join_remain(&ret, &str, &start, &end);
	return (ret);
}
