/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:14:23 by haeem             #+#    #+#             */
/*   Updated: 2023/09/15 17:38:24 by haeem            ###   ########seoul.kr  */
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

// free exactly one bucket
void	free_bucket(t_bucket *bucket)
{
	t_bucket	*tmp;

	tmp = bucket;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

// free all buckets in a hashmap
void	free_hashmap(t_hashmap *hashmap)
{
	size_t		i;
	t_bucket	*tmp;

	i = 0;
	while (i < hashmap->size)
	{
		tmp = hashmap->buckets[i];
		if (tmp != NULL)
		{
			free_bucket(tmp);
			hashmap->buckets[i] = NULL;
		}
		i++;
	}
	free(hashmap->buckets);
	free(hashmap);
}

// print all buckets in a hashmap
void	print_hashmap(t_hashmap *hashmap)
{
	size_t		i;
	t_bucket	*tmp;

	i = 0;
	while (i < hashmap->size)
	{
		tmp = hashmap->buckets[i];
		if (tmp != NULL)
		{
			printf("%s=%s\n", tmp->key, tmp->value);
		}
		i++;
	}
}
