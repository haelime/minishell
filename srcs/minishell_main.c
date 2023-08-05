/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/08/05 22:07:32 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

void	init_shell(void)
{

}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	char	*input;
	t_lst	*chunks;
	t_ast	*syntax;
	t_hashmap	*envmap;

	(void)argc;
	(void)argv;
	cmd.envp = envp;
	hash_envp(&cmd);
	// init_shell();
	while (1)
	{
		parse(&cmd);
		execute(&cmd);
	}
	return (0);
}

// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
// add_history, printf, malloc, free, write, access, open, read, close,
// fork, wait, waitpid, wait3, wait4,
// signal, sigaction, sigemptyset, sigaddset, kill, exit,
// gextcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe,
// opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot,
// ioctl, getenv,
// tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs