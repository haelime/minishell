/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:58:38 by haeem             #+#    #+#             */
/*   Updated: 2023/09/29 13:35:19 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// printf
# include <stdio.h>
// malloc, free, getenv, exit,
# include <stdlib.h>

// void* __debug_tmp;
// #define malloc(x) \
// (__debug_tmp = malloc(x));\
// printf("malloc(%lu) = %p, [%s:%d]\n", x, __debug_tmp, __FILE__, __LINE__)
// #define free(x) \
// if (x == NULL) \
//     printf("free(NULL), [%s:%d]\n", __FILE__, __LINE__); \
// free(x)

// close, read, write, unlink, fork, dup, dup2, pipe,
// execve, getcwd, chdir, isatty, ttyname, ttyslot
# include <unistd.h>
// open
# include <fcntl.h>
# include <stdbool.h>
// strerror
# include <string.h>

// opendir, closedir, readdir
# include <dirent.h>

// readline, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/readline.h>
// add_history
# include <readline/history.h>

// tcgetattr, tcsetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>
# include <termcap.h>
# include <termios.h>

# include <sys/types.h>
// stat, lstat, fstat
# include <sys/stat.h>

// kill, signal
# include <signal.h>
// wait3, wait4, wait, waitpid
# include <sys/wait.h>

// ioctl
# include <sys/ioctl.h>

// errno
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
char		*malloc_find_completed_cmd(t_token *cmd, char **paths);
void		read_heredoc(char *delim, int fd_heredoc, t_hashmap *envmap);
int			get_input_heredoc(
	t_cmd_block	*cmd_block, t_redirect *redirect, t_hashmap *envmap);
int			get_input_heredocs(t_list *cmd_blocks, t_hashmap *envmap);
int			fork_get_all_heredocs(t_list *cmd_blocks, t_hashmap *envmap);
void		close_pipes(int *pipes, int num_cmd);
int			*malloc_open_pipe(int num_cmd);
int			connect_stdin(t_cmd_block *cmd_block, int *pipes);
int			connect_stdout(
	t_cmd_block *cmd_block, int num_cmd, int *pipes);
int			connect_stdio(
	t_cmd_block *cmd_block, int num_cmd, int *pipes);
void		insert_exit_status(t_hashmap *envmap, int exitstatus);
char		**malloc_get_paths(t_hashmap *envmap);
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
char		*join_remain(char **o_ret, char **o_str, char **o_start, char **o_end);
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

#endif
