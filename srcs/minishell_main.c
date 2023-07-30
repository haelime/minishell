/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/07/30 20:25:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

void	init_shell(void)
{
	char	*termtype;
	int		success;

	termtype = getenv("TERM");
	if (termtype == 0)
	{
		ft_putstr_fd("Specify a terminal type with 'setenv TERM <yourtype>'.\n", 2);
		exit(0);
	}
	success = tgetent(0, termtype);
	if (success < 0)
	{
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
		exit(0);
	}
	if (success == 0)
	{
		ft_putstr_fd("Terminal type '", 2);
		ft_putstr_fd(termtype, 2);
		ft_putstr_fd("' is not defined.\n", 2);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	cmd.envp = envp;
	init_shell();
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