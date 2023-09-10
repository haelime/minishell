/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:33 by haeem             #+#    #+#             */
/*   Updated: 2023/09/10 19:58:12 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parsetree.h"
#include "../../include/hashlib.h"

void	exec_redirect(t_tree *syntax, t_hashmap *envmap)
{
	t_token	*token;

	token = syntax->data;
	(void)envmap;
}

void	exec_pipe(t_tree *syntax, t_hashmap *envmap)
{
	t_token	*token;

	token = syntax->data;
	(void)envmap;
}

void	exec_subshell(t_tree *syntax, t_hashmap *envmap)
{
	t_token	*token;

	token = syntax->data;
	(void)envmap;
}

void	exec_word(t_tree *syntax, t_hashmap *envmap)
{
	t_token	*token;

	token = syntax->data;
	(void)envmap;
}

void	execute(t_tree *syntax, t_hashmap *envmap)
{
	int		fd[2];
	t_token	*token;

	if (syntax == NULL)
		return ;
	dup_stdio(fd[0], fd[1]);
	if (!rec_check_syntax(syntax))
	{
		printf ("syntax error\n");
		return ;
	}
	else
	{
		token = (t_token *)(syntax->data);
		token->exec(syntax, envmap);
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}
