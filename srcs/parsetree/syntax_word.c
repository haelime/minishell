/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:50:18 by haeem             #+#    #+#             */
/*   Updated: 2023/09/05 18:57:30 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

// try to find key with long string,
// and if not found, try to find key with shorter string
char	*get_env(char *str, int i, t_hashmap *envmap)
{
	char	*key;
	char	*value;
	char	*ret;

	key = ft_substr(str, 0, i);
	value = hashmap_search(envmap, key);
	if (value)
	{
		ret = ft_strjoin(value, str + i + 1);
		free (key);
		return (ret);
	}
	else
	{
		free (key);
		return (get_env(str, i - 1, envmap));
	}
}

// dup original string and replace $ with value
char	*replace_dollar(char *str, t_hashmap *envmap)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			ret = ft_substr(str, 0, i);
			ret = ft_strjoin(ret, get_env(str + i + 1,
						ft_strlen(str + i + 1), envmap));
		}
		i++;
	}
}

void	rec_replace_dollar(t_tree *syntax, t_hashmap *envmap)
{
	const t_type	type = ((t_token *)(syntax->data))->type;
	t_token			*token;

	token = syntax->data;
	if (type == WORD)
	{
		token->str = replace_dollar(token->str, envmap);
	}
	if (syntax->left)
		rec_replace_dollar(syntax->left, envmap);
	if (syntax->right)
		rec_replace_dollar(syntax->right, envmap);
}
