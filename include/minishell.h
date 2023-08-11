/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/08/09 19:34:34 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// printf on <stdio.h>
# include <stdio.h>
// malloc on <stdlib.h>
// free on <stdlib.h>
// getenv on <stdlib.h>
// exit on <stdlib.h>
# include <stdlib.h>

// void* __debug_tmp;
// #define malloc(x) \
// (__debug_tmp = malloc(x));\
// printf("malloc(%lu) = %p, [%s:%d]\n", x, __debug_tmp, __FILE__, __LINE__)
// #define free(x) \
// if (x == NULL) \
//     printf("free(NULL), [%s:%d]\n", __FILE__, __LINE__); \
// free(x)

// close on <unistd.h>
// read on <unistd.h>
// write on <unistd.h>
// unlink on <unistd.h>
// fork on <unistd.h>
// dup on <unistd.h>
// dup2 on <unistd.h>
// pipe on <unistd.h>
// execve on <unistd.h>
// getcwd on <unistd.h>
// chdir on <unistd.h>
// isatty on <unistd.h>
// ttyname on <unistd.h>
// ttyslot on <unistd.h>
# include <unistd.h>
// open on <fcntl.h>
# include <fcntl.h>
# include <stdbool.h>
// strerror on <string.h>
# include <string.h>

// opendir on <dirent.h>
// closedir on <dirent.h>
// readdir on <dirent.h>
# include <dirent.h>

// readline on <readline/readline.h>
// rl_on_new_line on <readline/readline.h>
// rl_replace_line on <readline/readline.h>
// rl_redisplay on <readline/readline.h>
# include <readline/readline.h>
// add_history on <readlien/history.h>
# include <readline/history.h>

// tcgetattr on <term.h>
// tcsetattr on <term.h>
// tgetent on <term.h>
// tgetflag on <term.h>
// tgetnum on <term.h>
// tgetstr on <term.h>
// tgoto on <term.h>
// tputs on <term.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>

# include <sys/types.h>
// stat on <sys/stat.h>
// lstat on <sys/stat.h>
// fstat on <sys/stat.h>
# include <sys/stat.h>

// kill on <signal.h>
// signal on <signal.h>
# include <signal.h>
// wait3 on <sys/wait.h>
// wait4 on <sys/wait.h>
// wait on <sys/wait.h>
// waitpid on <sys/wait.h>
# include <sys/wait.h>

// ioctl on <sys/ioctl.h>
# include <sys/ioctl.h>

// errno on <errno.h>
# include <errno.h>

# include "hashlib.h"

# define PROMPT "minishell> "

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}	t_lst;

void	init_shell(int argc, char **argv, char **envp, t_hashmap *envmap);
void	init_envp(int argc, char **argv, char **envp, t_hashmap *envmap);

void	echoctl_off(void);
void	echoctl_on(void);
#endif
