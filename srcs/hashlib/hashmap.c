/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:05:16 by haeem             #+#    #+#             */
/*   Updated: 2023/08/15 18:17:29 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"
#include "../../libft/include/libft.h"

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
	unsigned int	hash;
	t_bucket		*newbucket;
	t_bucket		*current;

	newbucket = (t_bucket *)malloc(sizeof(t_bucket));
	hash = hash_string(key);
	newbucket->key = ft_strdup(key);
	newbucket->value = ft_strdup(value);
	newbucket->next = NULL;
	if (hashmap->buckets[hash % hashmap->size] == NULL)
		hashmap->buckets[hash % hashmap->size] = newbucket;
	else
	{
		current = hashmap->buckets[hash % hashmap->size];
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			return ;
		}
		while (current->next != NULL)
			current = current->next;
		current->next = newbucket;
	}
}

// simple hash search
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

// simple hash remove
int	hashmap_remove(t_hashmap *hashmap, const char *key)
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
			return (1);
		}
		prev = bucket;
		bucket = bucket->next;
	}
	return (0);
}
