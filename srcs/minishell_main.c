/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 16:57:45 by haeem             #+#    #+#             */
/*   Updated: 2023/08/09 19:27:32 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/hashlib.h"
#include "../include/astreelib.h"
#include "../libft/include/libft.h"

bool	quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\"')
			cmd = ft_strchr(cmd + 1, '\"');
		if (cmd == NULL)
			return (false);
		if (*cmd == '\'')
			cmd = ft_strchr(cmd + 1, '\'');
		if (cmd == NULL)
			return (false);
		++cmd;
	}
	return (true);
}

void	get_input(char *input, t_hashmap *envmap)
{
	input = readline(hashmap_search(envmap, "PS1"));
	if (input == NULL)
	{
		printf ("exit\n");
		exit(0);
	}
	if (ft_strlen(input) == 0 || ft_isempty(input))
	{
		free(input);
		return ;
	}
	add_history(input);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_hashmap	*envmap;
	// t_lst		*chunks;
	// t_ast		*syntax;

	input = NULL;
	envmap = hash_envp(envp);
	init_shell(argc, argv, envp, envmap);
	while (1)
	{
		get_input(input, envmap);
		// parse(str);
		// execute(str);
	}
	return (0);
}

// int main(void)
// {
// 	t_hashmap	*hashmap;
// 	char		*str;

// 	hashmap = hashmap_create(256);
// 	hashmap_insert(hashmap, "PATH=/usr/bin");
// 	hashmap_insert(hashmap, "HOME=/Users/haeem");
// 	hashmap_insert(hashmap, "PWD=/Users/haeem");
// 	hashmap_insert(hashmap, "OLDPWD=/Users/haeem");
// 	hashmap_insert(hashmap, "USER=haeem");
// 	hashmap_insert(hashmap, "LOGNAME=haeem");
// 	hashmap_insert(hashmap, "SHLVL=1");
// 	hashmap_insert(hashmap, "TERM=xterm-256color");

// 	str = hashmap_search(hashmap, "PATH");
// 	printf("PATH: %s\n", str);
// 	str = hashmap_search(hashmap, "HOME");
// 	printf("HOME: %s\n", str);
// 	str = hashmap_search(hashmap, "PWD");
// 	printf("PWD: %s\n", str);
// 	str = hashmap_search(hashmap, "OLDPWD");
// 	printf("OLDPWD: %s\n", str);
// 	str = hashmap_search(hashmap, "USER");
// 	printf("USER: %s\n", str);
// 	str = hashmap_search(hashmap, "LOGNAME");
// 	printf("LOGNAME: %s\n", str);
// 	str = hashmap_search(hashmap, "SHLVL");
// 	printf("SHLVL: %s\n", str);
// 	str = hashmap_search(hashmap, "TERM");
// 	printf("TERM: %s\n", str);

// 	return (0);
// }
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,
// add_history, printf, malloc, free, write, access, open, read, close,
// fork, wait, waitpid, wait3, wait4,
// signal, sigaction, sigemptyset, sigaddset, kill, exit,
// gextcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe,
// opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot,
// ioctl, getenv,
// tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs