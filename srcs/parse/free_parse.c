/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:55:58 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/21 19:38:46 by hyunjunk         ###   ########.fr       */
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
		free(p->content);
		free(p);
		p = next;
	}
	*out_cmd_blocks = NULL;
}
