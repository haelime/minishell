/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/07/30 20:36:33 by haeem            ###   ########seoul.kr  */
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

# include <errno.h>

# define PROMPT "minishell> "

typedef enum e_token
{
	WORD,
	PIPE,
	SEMICOLON,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HERE_DOC,
	REDIRECT_HERE_STRING,
	REDIRECT_ERROR,
	END_OF_FILE,
}t_token;

typedef struct s_ast
{
	char			*cmd;
	char			**envp;
	struct s_ast	*left;
	struct s_ast	*right;
}t_ast;
typedef struct s_cmd
{
	char	*cmd;
	char	**envp;

}t_cmd;

#endif