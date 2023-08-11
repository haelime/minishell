/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:02 by haeem             #+#    #+#             */
/*   Updated: 2023/08/09 19:54:12 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include "../../include/hashlib.h"

// ignore signal temporarily 
void	init_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

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
	// (void)argc;
	// (void)argv;
	// (void)envp;
	// (void)envmap;
	printf("hello minishell\n");
	init_signal();
	echoctl_off();
	init_envp(argc, argv, envp, envmap);
	init_readline();
}
