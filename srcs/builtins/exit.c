/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:27 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 19:42:11 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// exit func only receives 0 ~ 255, so msh does it too
// maybe should replace exit to return.
int	builtin_exit(char **argv)
{
	unsigned char	exitcode;

	if (argv[1] == NULL)
		exit(SUCCESS);
	if (!isdigit(*argv[1]))
		str_msg_exit("exit: %s numeric argument required\n",
			argv[1], NOTNUMERIC);
	else if (argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	exitcode = ft_atoi(argv[1]);
	exit(exitcode);
}
