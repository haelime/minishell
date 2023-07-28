/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 01:59:27 by haeem             #+#    #+#             */
/*   Updated: 2023/04/23 19:39:39 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"

int	*ft_set_char_table(const char *charset)
{
	int			i;
	static int	set[256];

	i = 0;
	if (charset == 0)
		return (0);
	while (i < 256)
	{
		set[i] = -1;
		i++;
	}
	i = 0;
	while (charset[i] != '\0')
	{
		set[(int) charset[i]] = i;
		i++;
	}
	return (set);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int				i;
	int				j;
	const size_t	s1len = ft_strlen(s1);
	const int		*charset = ft_set_char_table(set);
	char			*trimedstr;

	i = 0;
	j = s1len;
	if (s1 == 0)
		return ((void *) NULL);
	while (charset[(int) s1[i]] != -1)
		i++;
	while (0 < j && charset[(int) s1[j - 1]] != -1 && i < j)
		j--;
	trimedstr = (char *)malloc(sizeof(char) * (j - i + 1));
	if (trimedstr == NULL)
		return (NULL);
	ft_strlcpy(trimedstr, s1 + i, j - i + 1);
	return (trimedstr);
}
// Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
// specified in ’set’ removed from the beginning and the end of the string.