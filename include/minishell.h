/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 22:43:36 by hyunjunk         ###   ########.fr       */
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
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	REDIRECT_HEREDOC,
	REDIRECT_HEREDOC_DELIMITER,
} t_type;

typedef enum e_exit
{
	SUCCESS = 0,
	FAILURE = 1,
	BUILTIN = 2,
	UNABLE_TO_EXECUTE = 126,
	COMMAND_NOT_FOUND = 127,
	ARGUMENT_OUT_OF_RANGE = 128,
	NOTNUMERIC = 255,
} t_exit;

typedef void	(*t_func)();
typedef struct s_token
{
	t_type		type;
	int			 flag;
	char 		*str;
	char		*path;
	t_func		exec;
}	t_token;

//	arg is uses shallow copy.
//  heredoc_file is uses malloc.
typedef struct s_redirect
{
	t_type	type;
	char	*str;
}	t_redirect;

/* 	Format : <cmd> <options> <redicrect...>
	It uses shallow copy.
	Don't remove original strings until this becomes not used
	Only options and completed_cmd use malloc.
	(The internal strings of options is not malloc) 
	
	@Exceptional case :		
	If input redirection is heredoc, 
	then heredoc_file will use malloc)	*/
typedef struct s_cmd_block
{
	t_tree_node_type	type;
	t_token				*cmd;
	int					num_options;
	char				**options;
	t_list				*redirects_in;
	t_list				*redirects_out;
	char				*heredoc_file;
	char				*completed_cmd;
	int					idx;
}	t_cmd_block;

typedef struct s_tree	t_tree;

// initiate shell
/* -------------------------------------------------------------------------- */
void		init_shell(int argc, char **argv, char **envp, t_hashmap *envmap);
void		init_envp(int argc, char **argv, char **envp, t_hashmap *envmap);
void		set_shlvl(t_hashmap *envmap);
void		set_ps1(t_hashmap *envmap);
void		set_cwd(t_hashmap *envmap);
void		set_special_var(t_hashmap *envmap);
void		set_path(t_hashmap *envmap);
/* -------------------------------------------------------------------------- */

// get input & parse
/* -------------------------------------------------------------------------- */
void		get_input(char **input);
/* -------------------------------------------------------------------------- */

// execute
/* -------------------------------------------------------------------------- */
void		execute(t_list *syntax, t_hashmap *envmap);
void		exec_redirect(t_tree *syntax, t_hashmap *envmap);
void		exec_pipe(t_tree *syntax, t_hashmap *envmap);
void		exec_subsh(t_tree *syntax, t_hashmap *envmap);
void		exec_word(t_tree *syntax, t_hashmap *envmap);
char		*malloc_find_completed_cmd(t_token *cmd, char **paths);
/* -------------------------------------------------------------------------- */

// utils
/* -------------------------------------------------------------------------- */
void		echoctl_off(void);
void		echoctl_on(void);
bool		isdoublequoted(char *str, int i);
bool		isquoted(char *str, int i);
bool		is_builtin(t_cmd_block *cmd_block);
void		dup_stdio(int in_fd, int out_fd);
void		print2d(t_tree *root);
void		print2dutil(t_tree *root, int space);
void		print_hashmap(t_hashmap *hashmap);
void		print_chunks(t_list *chunks);
void		msg_exit(const char *str, int err_code);
void		str_msg_exit(const char *str, const char *str_arg, int err_code);
int			str_msg_ret(const char *str, const char *str_arg, int err_code);
char		*ft_strdup_null(const char *src);
/* -------------------------------------------------------------------------- */

/* Signal Handler <signal.c> */
/* -------------------------------------------------------------------------- */
void		signal_ignore(void);
void		signal_interactive(void);
void		signal_default(void);
/* -------------------------------------------------------------------------- */

/* parse */
/* -------------------------------------------------------------------------- */
/*	@summary	Separates the input into tokens to return.
				If the input is invalid and can't be parsed,
				then returns NULL and handle the memory release internally */
t_list		*parse(char *input, t_hashmap *envmap);
void		tokenize(char *input, t_list **out_chunks);
bool		istoken(char ch);
bool		isanotherquote(char *begin);
bool		isparenclosed(char *begin);
char		*tryfutherparen(char *begin);
void		rec_replace_dollar(t_tree *syntax, t_hashmap *envmap);
char		*replace_dollar(char *str, t_hashmap *envmap);
void		print_pstree(t_tree *syntax);
void		make_cmd_blocks_by_tokens(t_list **out_list_cmd_blocks, t_list *list_tokens);
int			check_parse_invalid(t_list *tokens);
void		free_tokens(t_list **out_tokens);
void		free_cmd_blocks(t_list **out_cmd_blocks);
/* -------------------------------------------------------------------------- */

// syntax
/* -------------------------------------------------------------------------- */
bool		rec_check_syntax(t_tree *syntax);
/* -------------------------------------------------------------------------- */

// builtins
/* -------------------------------------------------------------------------- */
int			builtin_env(char **argv, t_hashmap *envmap);
int			builtin_pwd(t_hashmap *hashmap);
int			builtin_export(char **argv, t_hashmap *envmap);
int			builtin_unset(char **argv, t_hashmap *envmap);
int			builtin_echo(char **argv);
int			builtin_cd(char **argv, t_hashmap *envmap);
int			builtin_exit(char **argv);
/* -------------------------------------------------------------------------- */

// debug
/* -------------------------------------------------------------------------- */
inline void		*__wrap_malloc(size_t size, const char* FILE, int LINE, const char* FUNCTION)
{
	void* ret = malloc(size);
	printf("malloc() %6lu.bytes %s:%d:%s() ADDR=%p\n",
		size, FILE, LINE, FUNCTION, ret);

	return ret;
}

inline void	__wrap_free(void* ptr, const char* FILE, int LINE, const char* FUNCTION)
{
	printf("free() %s:%d:%s() ADDR=%p value={%s}\n",
		FILE, LINE, FUNCTION, ptr, (char*)ptr);
	free(ptr);
}

// #define malloc(x) __wrap_malloc(x, __FILE__, __LINE__, __FUNCTION__)
// #define free(x) __wrap_free(x, __FILE__, __LINE__, __FUNCTION__);
/* -------------------------------------------------------------------------- */

#endif
