/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:01:43 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 18:10:24 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = src[j];
	return (dest);
}

// SEGFAULT IF EITHER IS NULL
char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1len = ft_strlen(s1);
	const size_t	s2len = ft_strlen(s2);
	const size_t	total_len = s1len + s2len + 1;
	char			*str;

	if (total_len == 1)
	{
		str = (char *)malloc(sizeof(char) * (1));
		if (str == NULL)
			return (NULL);
		str[0] = 0;
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (total_len));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, total_len);
	if (s1len == 0)
		return (ft_strcat(str, s2));
	else if (s2len == 0)
		return (ft_strcat(str, s1));
	ft_strcat(str, s1);
	ft_strcat(str, s2);
	return (str);
}

char	*ft_strjoinfree(char **out_s1, char **out_s2)
{
	const size_t	s1len = ft_strlen(*out_s1);
	const size_t	s2len = ft_strlen(*out_s2);
	const size_t	total_len = s1len + s2len + 1;
	char			*str;

	str = (char *)malloc(sizeof(char) * (total_len));
	ft_bzero(str, total_len);
	ft_strcat(str, *out_s1);
	ft_strcat(str, *out_s2);
	free(*out_s1);
	free(*out_s2);
	*out_s1 = NULL;
	*out_s2 = NULL;
	return (str);
}
