/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:16:28 by haeem             #+#    #+#             */
/*   Updated: 2023/01/27 12:06:02 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_dup(int *i, int total_len, t_fd_list *s, t_string *ret)
{
	while (*i < total_len && s->offset < s->buf_max)
	{	
		ret->p[(*i)++] = s->buf[s->offset++];
		if (ret->p[*i - 1] == '\n')
			return ;
	}
	return ;
}

void	ft_freer(t_string *s1, int *i, t_string *ret)
{
	free(s1->p);
	ret->p[*i] = '\0';
	s1->len = *i;
}

// copy buffer [offset to buf_max], if it meets \n or EOF, return it.
char	*ft_streamjoin(t_string *s1, t_fd_list *s)
{
	t_string	ret;
	int			total_len;
	int			i;

	i = -1;
	s1->len = ft_strlen(s1->p);
	total_len = s1->len + s->buf_max - s->offset;
	if (total_len <= 0)
		return (NULL);
	ret.p = (char *)malloc(sizeof(char) * (total_len + 1));
	while (++i < s1->len)
	{
		ret.p[i] = s1->p[i];
		if (ret.p[i] == '\n')
		{
			free(s1->p);
			s1->len = i;
			ret.p[i + 1] = '\0';
			return (ret.p);
		}
	}
	ft_dup(&i, total_len, s, &ret);
	ft_freer(s1, &i, &ret);
	return (ret.p);
}
