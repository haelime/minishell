/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:28:02 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 13:31:03 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_invalid_identifier(char *key)
{
	char	*p;

	p = key;
	while (*p != '\0')
	{
		if (!ft_isalpha(*p) && !ft_isdigit(*p) && *p != '_')
			return (1);
		p++;
	}
	return (0);
}

void	free_key_value(char **key, char **value)
{
	free(*key);
	free(*value);
}
