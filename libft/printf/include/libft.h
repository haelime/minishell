/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:09:44 by haeem             #+#    #+#             */
/*   Updated: 2023/02/07 03:30:07 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# define TRUE (1)
# define FALSE (0)

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t cnt, size_t size);
int		ft_isalpha(int ch);
int		ft_isalnum(int ch);
int		ft_isascii(int ch);
int		ft_isdigit(int ch);
int		ft_isprint(int ch);
void	*ft_memchr(const void *p, int value, size_t num);
int		ft_memcmp(const void *p1, const void *p2, size_t num);
void	*ft_memcpy(void *dest, const void *src, size_t cnt);
void	*ft_memmove(void *dest, const void *src, size_t cnt);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strcat(char *dest, const char *src);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *str, int ch);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_strnlen(const char *str, size_t maxlen);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strrchr(const char *str, int ch);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_tolower(int ch);
int		ft_toupper(int ch);
void	ft_swap(int *a, int *b);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(const char *s, char c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_putnbr_base(const long long nbr, const char *base);

// bonus
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *newlist);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newlist);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif 
