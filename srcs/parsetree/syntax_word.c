/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 17:50:18 by haeem             #+#    #+#             */
/*   Updated: 2023/09/07 21:40:53 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

// make key, from $ to null, $ or ' '
char	*make_key(char *str, int i)
{
	int		j;
	char	*key;

	j = i + 1;
	while (str[j] && str[j] != ' ' && str[j] != '$' && str[j] != '\"'
		&& str[j] != '\'' && str[j] != '>' && str[j] != '<' && str[j] != '|')
		j++;
	key = ft_substr(str, i, j - i);
	return (key);
}

// dollar to env if not quoted
char	*replace_dollar(char *str, t_hashmap *envmap)
{
	int		i;
	int		flag;
	char	*key;
	char	*tmp;
	char	*tmp2;

	i = -1;
	flag = 0;
	tmp = ft_strdup(str);
	while (tmp[++i])
	{
		if (tmp[i] == '\'')
			flag = !flag;
		if (tmp[i] == '$' && !flag)
		{
			key = make_key(tmp, i);
			tmp2 = ft_strreplace(tmp, key, hashmap_search(envmap, key + 1));
			free (tmp);
			tmp = tmp2;
			free (key);
		}
	}
	free (str);
	return (tmp);
}

void	rec_replace_dollar(t_tree *syntax, t_hashmap *envmap)
{
	const t_type	type = ((t_token *)(syntax->data))->type;
	t_token			*token;

	token = syntax->data;
	if (type == WORD)
	{

		if (ft_strchr(token->str, '$'))
			token->str = replace_dollar(token->str, envmap);
	}
	if (syntax->left)
		rec_replace_dollar(syntax->left, envmap);
	if (syntax->right)
		rec_replace_dollar(syntax->right, envmap);
}
