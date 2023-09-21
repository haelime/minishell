/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:05:16 by haeem             #+#    #+#             */
/*   Updated: 2023/09/21 17:13:36 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

// FNV hash algorithm
unsigned int	hash_string(const char *s)
{
	unsigned int	i;
	char			*ptr;

	i = FNV_OFFSET;
	ptr = (char *)s;
	while (*ptr != '\0')
	{
		i += (i << 1) + (i << 4) + (i << 7) + (i << 8) + (i << 24);
		i ^= *ptr;
		ptr++;
	}
	return (i);
}

// create hash table with size SHOULD BE 2^n
t_hashmap	*hashmap_create(int size)
{
	t_hashmap	*newmap;
	int			i;

	newmap = (t_hashmap *)malloc(sizeof(t_hashmap));
	newmap->size = size;
	newmap->buckets = (t_bucket **)malloc(sizeof(t_bucket *) * size);
	i = 0;
	while (i < size)
	{
		newmap->buckets[i] = NULL;
		i++;
	}
	return (newmap);
}

// simple hash insert
void	hashmap_insert(t_hashmap *hashmap, char *key, char *value)
{
	const unsigned int	hash = hash_string(key);
	t_bucket			**ptr_new_place;
	t_bucket			*current;

	if (hashmap->buckets[hash % hashmap->size] == NULL)
		ptr_new_place = &hashmap->buckets[hash % hashmap->size];
	else
	{
		current = hashmap->buckets[hash % hashmap->size];
		while (current->next != NULL)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				free(current->value);
				current->value = ft_strdup(value);
				return ;
			}
			current = current->next;
		}
		ptr_new_place = &current->next;
	}
	*ptr_new_place = (t_bucket *)malloc(sizeof(t_bucket));
	(*ptr_new_place)->key = ft_strdup(key);
	(*ptr_new_place)->value = ft_strdup(value);
	(*ptr_new_place)->next = NULL;
}

// returns hash value of string, if string is NULL, returns NULL
char	*hashmap_search(t_hashmap *hashmap, const char *key)
{
	unsigned int	hash;
	t_bucket		*bucket;

	hash = hash_string(key);
	if (hashmap->buckets[hash % hashmap->size] == NULL)
		return (NULL);
	bucket = hashmap->buckets[hash % hashmap->size];
	while (bucket)
	{
		if (ft_strcmp(bucket->key, key) == 0)
			return (bucket->value);
		bucket = bucket->next;
	}
	return (NULL);
}

// find exact string, remove it from hashmap, and free it
// if success, returns 0, else 1
bool	hashmap_remove(t_hashmap *hashmap, const char *key)
{
	unsigned int	hash;
	t_bucket		*bucket;
	t_bucket		*prev;

	hash = hash_string(key);
	if (hashmap->buckets[hash % hashmap->size] == NULL)
		return (0);
	bucket = hashmap->buckets[hash % hashmap->size];
	prev = NULL;
	while (bucket)
	{
		if (ft_strcmp(bucket->key, key) == 0)
		{
			if (prev == NULL)
				hashmap->buckets[hash % hashmap->size] = bucket->next;
			else
				prev->next = bucket->next;
			free_bucket(bucket);
			return (0);
		}
		prev = bucket;
		bucket = bucket->next;
	}
	return (1);
}
