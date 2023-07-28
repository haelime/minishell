/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:18:38 by haeem             #+#    #+#             */
/*   Updated: 2023/04/16 18:10:04 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE (1024)
# endif

# define MAX_STREAM (5)

typedef struct s_fd_list
{
	int					fd;
	char				buf[BUFFER_SIZE];
	int					offset;	
	int					buf_max;
	struct s_fd_list	*next;
}t_fd_list;

typedef struct s_string
{
	char	*p;
	int		len;
}t_string;

char		*get_next_line(int fd);
t_fd_list	*ft_get_stream(t_fd_list *fd_list[MAX_STREAM], int fd);
t_fd_list	*ft_init_stream(t_fd_list *fd_list[MAX_STREAM], int fd);
char		*ft_read_fd(t_fd_list *string_stream);
void		ft_free_all_list(t_fd_list *fd_list[MAX_STREAM], int fd);

size_t		ft_strlen(const char *str);
void		ft_dup(int *i, int total_len, t_fd_list *s, t_string *ret);
void		ft_freer(t_string *s1, int *i, t_string *ret);
char		*ft_streamjoin(t_string *s1, t_fd_list *string_stream);
#endif