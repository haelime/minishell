/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/07/28 17:48:56 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
# include <readline/readline.h>
# include <readline/history.h>

// termcap, termios
# include <termcap.h>
# include <termios.h>

// stat, lstat, fstat
# include <sys/types.h>
# include <sys/stat.h>
// open, close, read, write, unlink, execve, dup, dup2, pipe
# include <fcntl.h>

# include <signal.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <termcap.h>

# define PROMPT "minishell> "

typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	char	**envp;
}t_cmd;

#endif