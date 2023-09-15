/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:21 by haeem             #+#    #+#             */
/*   Updated: 2023/09/15 19:26:22 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// -n option: don't print the trailing newline character
int	builtin_echo(char **argv)
{
	int		i;
	bool	isn;

	isn = 0;
	if (*(argv + 1) == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	if (ft_strcmp(*(argv + 1), "-n") == 0)
		isn = 1;
	i = isn + 1;
	while (*(argv + i))
	{
		printf("%s", *(argv + i));
		if (*(argv + i + 1))
			printf(" ");
		i++;
	}
	if (!isn)
		printf("\n");
	return (SUCCESS);
}