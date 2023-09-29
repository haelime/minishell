/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:55:58 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/29 13:36:40 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_tokens(t_list **out_tokens)
{
	t_list	*p;
	t_list	*next;
	t_token	*token;

	if (*out_tokens == NULL)
		return ;
	p = *out_tokens;
	while (p != NULL)
	{
		token = (t_token *)p->content;
		next = p->next;
		free(token->str);
		free(p->content);
		free(p);
		p = next;
	}
	*out_tokens = NULL;
}

void	free_redirects(t_list **out_redirects)
{
	t_list		*p;
	t_list		*next;
	t_redirect	*redirect;

	if (*out_redirects == NULL)
		return ;
	p = *out_redirects;
	while (p != NULL)
	{
		redirect = (t_redirect *)p->content;
		next = p->next;
		free(p->content);
		free(p);
		p = next;
	}
	*out_redirects = NULL;
}

void	free_cmd_blocks(t_list **out_cmd_blocks)
{
	t_list		*p;
	t_list		*next;
	t_cmd_block	*cmd_block;

	if (*out_cmd_blocks == NULL)
		return ;
	p = *out_cmd_blocks;
	while (p != NULL)
	{
		cmd_block = (t_cmd_block *)p->content;
		next = p->next;
		free(cmd_block->options);
		free(cmd_block->completed_cmd);
		free_redirects(&cmd_block->redirects_in);
		free_redirects(&cmd_block->redirects_out);
		if (cmd_block->heredoc_file
			&& access(cmd_block->heredoc_file, W_OK) == 0)
			unlink(cmd_block->heredoc_file);
		free(cmd_block->heredoc_file);
		free(p->content);
		free(p);
		p = next;
	}
	*out_cmd_blocks = NULL;
}
