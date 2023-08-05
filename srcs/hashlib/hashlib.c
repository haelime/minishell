/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashlib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:05:16 by haeem             #+#    #+#             */
/*   Updated: 2023/08/05 22:07:31 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"

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

// hash table
t_hashmap	*hash_create(int size)
{
	t_hashmap	*newmap;
	int			i;

	newmap = (t_hashmap *)malloc(sizeof(t_hashmap));
	if (!newmap)
		return (NULL);
	newmap->size = size;
	newmap->buckets = (t_bucket **)malloc(sizeof(t_bucket *) * size);
	if (!newmap->buckets)
		return (NULL);
	i = 0;
	while (i < size)
	{
		newmap->buckets[i] = NULL;
		i++;
	}
	return (newmap);
}

// hash insert
int	hash_insert(t_hashmap hashmap, char *envp)
{
	
}

// hash search
char	*hash_search(t_hashmap hashmap, const char *key)
{

}

