/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:58 by haeem             #+#    #+#             */
/*   Updated: 2023/09/18 16:15:28 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHLIB_H
# define HASHLIB_H

// Fowler-Noll-Vo's magic number for 32 bits
# define FNV_OFFSET (2166136261)
# define FNV_PRIME (16777619)

typedef struct s_bucket
{
	struct s_bucket	*next;
	char			*key;
	char			*value;

}				t_bucket;

typedef struct s_hashmap
{
	t_bucket		**buckets;
	unsigned int	size;
}				t_hashmap;

// Hash function for string
t_hashmap		*hash_envp(char **envp);

t_hashmap		*hashmap_create(int size);
void			hashmap_insert(t_hashmap *hashmap, char *key, char *value);
char			*hashmap_search(t_hashmap *hashmap, const char *key);
bool			hashmap_remove(t_hashmap *hashmap, const char *key);

unsigned int	hash_string(const char *s);
void			free_bucket(t_bucket *bucket);
void			free_hashmap(t_hashmap *hashmap);
void			print_hashmap(t_hashmap *hashmap);
char			**malloc_get_envp(t_hashmap *hashmap);

#endif