/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:02 by haeem             #+#    #+#             */
/*   Updated: 2023/08/11 20:21:30 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"
#include "../../include/hashlib.h"

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGTERM, sigterm_handler);
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
