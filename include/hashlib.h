/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 19:33:58 by haeem             #+#    #+#             */
/*   Updated: 2023/08/05 20:28:37 by haeem            ###   ########seoul.kr  */
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
	void			*value;

}				t_bucket;

typedef struct s_hashmap
{
	t_bucket		**buckets;
	unsigned int	size;
}				t_hashmap;

// Hash function for string
unsigned int	hash_string(const char *s);

#endif