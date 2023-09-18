/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:14:23 by haeem             #+#    #+#             */
/*   Updated: 2023/09/18 17:18:20 by hyunjunk         ###   ########.fr       */
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

int	get_count_hashmap(t_hashmap	*hashmap)
{
	t_bucket		*p;
	unsigned int	i;
	int				count;

	count = 0;
	i = 0;
	while (i < hashmap->size)
	{
		p = hashmap->buckets[i];
		while (p != NULL)
		{
			count += 1;
			p = p->next;
		}
		i++;
	}
	return (count);
}

char	**malloc_get_envp(t_hashmap *hashmap)
{
	unsigned int	bucket_i;
	unsigned int	envp_i;
	t_bucket		*tmp;
	char			**ret_envp;

	ret_envp = (char **)malloc(
			(get_count_hashmap(hashmap) + 1) * sizeof(char *));
	ret_envp[hashmap->size] = NULL;
	bucket_i = 0;
	envp_i = 0;
	while (bucket_i < hashmap->size)
	{
		tmp = hashmap->buckets[bucket_i++];
		while (tmp != NULL)
		{
			ret_envp[envp_i] = malloc(
					(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
			ft_strcpy(ret_envp[envp_i], tmp->key);
			ret_envp[envp_i][ft_strlen(tmp->key)] = '=';
			ft_strcpy(ret_envp[envp_i] + ft_strlen(tmp->key) + 1, tmp->value);
			envp_i += 1;
			tmp = tmp->next;
		}
	}
	return (ret_envp);
}
