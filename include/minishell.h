/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/08/28 20:25:27 by haeem            ###   ########seoul.kr  */
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

#ifndef HASHLIB_H
# include "hashlib.h"
#endif

#ifndef PARSETREE_H
# include "parsetree.h"
#endif

#ifndef LIBFT_H
# include "../libft/include/libft.h"
#endif

#define DOUBLEQUOTE (1)
#define QUOTE (2)
#define SUBSHELL (4)
#define FAILED (8)

#define STDIN (0)
#define STDOUT (1)
#define STDERR (2)

typedef enum e_type
{
	WORD,
	WHITESPACE,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	REDIRECT_HEREDOC_DELIMITER,
	DOUBLE_PIPE,
	DOUBLE_AND,
	SUBSH,
	END
} t_type;

typedef struct s_token
{
	t_type		type;
	int			flag;
	char 		*str;
	char		*path;
}	t_token;

typedef struct s_pstree	t_pstree;

// initiate shell
/* -------------------------------------------------------------------------- */
void		init_shell(int argc, char **argv, char **envp, t_hashmap *envmap);
void		init_envp(int argc, char **argv, char **envp, t_hashmap *envmap);
void		set_shlvl(t_hashmap *envmap);
void		set_ps1(t_hashmap *envmap);
void		set_cwd(t_hashmap *envmap);
void		set_special_var(t_hashmap *envmap);
/* -------------------------------------------------------------------------- */

// get input & parse
/* -------------------------------------------------------------------------- */
void		get_input(char **input, t_hashmap *envmap);
/* -------------------------------------------------------------------------- */

// utils
/* -------------------------------------------------------------------------- */
void		echoctl_off(void);
void		echoctl_on(void);
/* -------------------------------------------------------------------------- */

/* Signal Handler <signal.c> */
/* -------------------------------------------------------------------------- */
void		signal_ignore(void);
void		signal_interactive(void);
void		signal_default(void);
/* -------------------------------------------------------------------------- */

/* parse */
/* -------------------------------------------------------------------------- */
t_pstree	*parse(char *input, t_hashmap *envmap);
t_list		*tokenize(char *input, t_list **chunks);
bool		istoken(char ch);
/* -------------------------------------------------------------------------- */

#endif
