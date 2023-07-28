/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/07/28 17:56:08 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/include/libft.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	char	*line;
	char	**cmd;

	argc = 0;
	argv = NULL;
	envp = NULL;
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "exit") == 0)
			break ;
		add_history(line);
		cmd = ft_split(line, ' ');
		i = -1;
		while (cmd[++i])
			printf("%s\n", cmd[i]);
		free(line);
		free(cmd);
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