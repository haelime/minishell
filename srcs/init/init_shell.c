/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:02 by haeem             #+#    #+#             */
/*   Updated: 2023/09/28 17:44:39 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include "../../include/hashlib.h"

// initialize readline for first prompt
void	init_readline(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_shell(int argc, char **argv, char **envp, t_hashmap *envmap)
{
	printf("hello minishell\n");
	signal_ignore();
	echoctl_off();
	init_envp(argc, argv, envp, envmap);
	init_readline();
}
