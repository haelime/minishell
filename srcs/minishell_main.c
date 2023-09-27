/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 19:10:37 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/hashlib.h"
#include "../include/parsetree.h"
#include "../libft/include/libft.h"

extern void		*__wrap_malloc(size_t size, const char* FILE, int LINE, const char* FUNCTION);
extern void		__wrap_free(void* ptr, const char* FILE, int LINE, const char* FUNCTION);

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_hashmap	*envmap;
	t_list		*tokens;
	t_list		*cmd_blocks;

	envmap = hash_envp(envp);
	init_shell(argc, argv, envp, envmap);
	while (1)
	{
		signal_interactive();
		get_input(&input, envmap);
		if (input == NULL || ft_strlen(input) == 0)
			continue ;
		tokens = parse(input, envmap);
		if (tokens == NULL)
			continue ;
		make_cmd_blocks_by_tokens(&cmd_blocks, tokens);
		execute(cmd_blocks, envmap);
		free(input);
		free_tokens(&tokens);
		free_cmd_blocks(&cmd_blocks);
	}
	return (0);
}

// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay, add_history,
// printf, malloc, free, write, access, open, read,
// close, fork, wait, waitpid, wait3, wait4, signal,
// sigaction, sigemptyset, sigaddset, kill, exit,
// getcwd, chdir, stat, lstat, fstat, unlink, execve,
// dup, dup2, pipe, opendir, readdir, closedir,
// strerror, perror, isatty, ttyname, ttyslot, ioctl,
// getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
// tgetnum, tgetstr, tgoto, tputs

// '<' : input redirection
// '>' : output redirection
// '<<' : heredoc
// '>>' : append

// 수정해야함
// <pipeline>     ::= <cmd>
//                |   <pipeline> '|' <cmd>

// <cmd>          ::= <simple_cmd> 
//                |   <simple_cmd> <redirects>

// <simple_cmd>   ::= <file_path>
//                |   <argv>

// <argv>         ::= <file_path> <args>

// <redirects>    ::= <io_redirect>
//                 |  <redirects> <io_redirect>

// <io_redirect>  ::= '<'   <filename>
//                 |  '<<'  <filename>
//                 |  '>'   <filename>
//                 |  '>>'  <filename>

// <args>        ::= WORD 
//                 | <args> WORD

// <file_path>   ::= WORD

// <filename>    ::= WORD