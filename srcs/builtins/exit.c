/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:27 by haeem             #+#    #+#             */
/*   Updated: 2023/09/21 19:50:48 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// exit func only receives 0 ~ 255, so msh does it too
// maybe should replace exit to return.
int	builtin_exit(char **argv)
{
	int				i;
	int				argc;
	unsigned char	exitcode;

	if (*(argv + 1) == NULL)
		exit(SUCCESS);
	else if (*(argv + 2) != NULL)
		exit(BUILTIN);
	while (*(++argv))
	{
		i = 0;
		while (*argv[i] != NULL)
		{
			if (!isdigit(*argv[i]))
				exit(NOTNUMERIC);
			i++;
		}
		exitcode = ft_atoi(*argv);
		exit(exitcode);
	}
}
