/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 01:15:28 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 20:48:38 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static size_t	wordcount(const char *s, char c)
{
	size_t	wc;
	size_t	i;

	i = 0;
	wc = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i] == c && s[i + 1] != '\0'
				&& s[i + 1] != c))
			wc++;
		i++;
	}
	return (wc);
}

void	ft_free_strings(char **strings)
{
	size_t	j;

	j = 0;
	while (strings[j])
	{
		free(strings[j]);
		j++;
	}
	free(strings);
	return (NULL);
}

static char	**spliter(char **words, int wc, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	tmp;

	i = 0;
	j = 0;
	while (i < wc && s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		tmp = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		words[i] = ft_strndup(&s[tmp], j - tmp);
		if (words[i] == NULL)
		{
			ft_free_strings(words);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(const char *s, char c)
{
	char			**words;
	const size_t	wc = wordcount(s, c);
	size_t			tmp;

	words = (char **)malloc(sizeof(char *) * (wc + 1));
	if (words == NULL)
		return (NULL);
	words = spliter(words, wc, s, c);
	return (words);
}
