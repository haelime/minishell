/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:16:24 by haeem             #+#    #+#             */
/*   Updated: 2023/01/27 12:06:29 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdbool.h>
#include <unistd.h>

// returns one line, else, returns NULL
char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list[MAX_STREAM];
	t_fd_list			*string_stream;
	char				*buffer;

	if (fd < 0)
		return (NULL);
	string_stream = ft_get_stream((t_fd_list **)fd_list, fd);
	if (string_stream == NULL)
		string_stream = ft_init_stream((t_fd_list **)fd_list, fd);
	buffer = ft_read_fd(string_stream);
	if (buffer == NULL)
	{
		ft_free_all_list((t_fd_list **)fd_list, fd);
		return (NULL);
	}
	return (buffer);
}

// search list array's hashed index to find exact fd
t_fd_list	*ft_get_stream(t_fd_list *fd_list[MAX_STREAM], int fd)
{
	t_fd_list	*ret;
	const int	hashed_idx = fd % MAX_STREAM;

	ret = fd_list[hashed_idx];
	if (ret == NULL)
		return (NULL);
	while (ret != NULL && ret->fd != fd)
		ret = ret->next;
	return (ret);
}

// initiate fd_list's first linked list
t_fd_list	*ft_init_stream(t_fd_list *fd_list[MAX_STREAM], int fd)
{
	t_fd_list	*new_list;
	const int	hashed_idx = fd % MAX_STREAM;

	new_list = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (new_list == NULL)
		return (NULL);
	new_list->fd = fd;
	new_list->offset = 0;
	new_list->buf_max = 0;
	new_list->next = fd_list[hashed_idx];
	fd_list[hashed_idx] = new_list;
	new_list->buf_max = read(fd, new_list->buf, BUFFER_SIZE);
	if (new_list->buf_max < 0)
		new_list->buf_max = 0;
	return (new_list);
}

// reads buffer & returns string ends with '\n' or EOF
char	*ft_read_fd(t_fd_list *string_stream)
{
	t_string	ret;

	ret.p = NULL;
	while (true)
	{
		if (string_stream->buf_max <= string_stream->offset)
		{
			string_stream->buf_max = read(string_stream->fd, string_stream->buf,
					BUFFER_SIZE);
			if (string_stream->buf_max == -1)
			{
				free(ret.p);
				return (NULL);
			}
			string_stream->offset = 0;
		}
		ret.p = ft_streamjoin(&ret, string_stream);
		if (ret.p == NULL)
			return (NULL);
		if (ret.p[ret.len - 1] == '\n')
			return (ret.p);
		if (string_stream->buf_max == 0)
			return (ret.p);
	}
	return (ret.p);
}

void	ft_free_all_list(t_fd_list *fd_list[MAX_STREAM], int fd)
{
	const int	hashed_idx = fd % MAX_STREAM;
	t_fd_list	**p;
	t_fd_list	*tmp;

	p = &fd_list[hashed_idx];
	while (*p != NULL)
	{
		if ((*p)->fd == fd)
		{
			tmp = (*p)->next;
			free(*p);
			*p = tmp;
			break ;
		}
		p = &(*p)->next;
	}
}

// typedef struct s_fd_list
// {
// 	int					fd;
// 	char				*buf;
// 	size_t				offset;	
// 	size_t				buf_max;
// 	struct s_fd_list	*next;
// }t_fd_list;