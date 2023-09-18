/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/18 18:18:35 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
@Return : returns the position of the chunk that should be read next. 
			It will be the position of PIPE or REDIRECT or NULL.
*/
static t_list	*fill_options_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_list		*pos_origin;
	int			i;

	pos_origin = pos;
	out_cmd_block->num_options = 1;
	while (pos != NULL && ((t_token *)pos->content)->type == WORD)
	{
		out_cmd_block->num_options += 1;
		pos = pos->next;
	}
	out_cmd_block->options = (char **)malloc(
			(out_cmd_block->num_options + 1) * sizeof(char *));
	out_cmd_block->options[out_cmd_block->num_options] = NULL;
	out_cmd_block->options[0] = out_cmd_block->cmd->str;
	pos = pos_origin;
	i = 1;
	while (pos != NULL && ((t_token *)pos->content)->type == WORD)
	{
		out_cmd_block->options[i++] = ((t_token *)pos->content)->str;
		pos = pos->next;
	}
	return (pos);
}

static void	malloc_options_default(t_cmd_block *cmd_block)
{
	if (cmd_block->options == NULL)
	{
		cmd_block->num_options = 1;
		cmd_block->options = (char **)malloc(2 * sizeof(char *));
		cmd_block->options[1] = NULL;
		cmd_block->options[0] = cmd_block->cmd->str;
	}
}

/*
@Return : returns the position of the chunk that should be read next. 
			It will be the position of PIPE or NULL.
*/
static t_list	*fill_subcontext_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_token		*token;
	t_token		*next_token;

	if (pos == NULL)
		malloc_options_default(out_cmd_block);	while (pos != NULL && ((t_token *)pos->content)->type != PIPE)
	{
		token = (t_token *)pos->content;
		if (token->type == WORD)
		{
			pos = fill_options_cmd_block(out_cmd_block, pos);
			continue ;
		}
		next_token = (t_token *)pos->next->content;
		if (token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
			out_cmd_block->redirect_in = next_token->str;
		if (token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
			out_cmd_block->redirect_out = next_token->str;
		out_cmd_block->redirect_is_heredoc = token->type == REDIRECT_HEREDOC;
		out_cmd_block->redirect_is_append = token->type == REDIRECT_APPEND;
		pos = pos->next->next;
	}
	return (pos);
}

/* It uses shallow copy about strings. 
	The caller should care about this. */
void	make_cmd_blocks_by_tokens(
	t_list **out_list_cmd_blocks, t_list *list_tokens)
{
	t_list		*now;
	t_cmd_block	*new_block;

	*out_list_cmd_blocks = NULL;
	now = list_tokens;
	while (now != NULL)
	{
		if (((t_token *)now->content)->type == PIPE)
			now = now->next;
		new_block = (t_cmd_block *)malloc(sizeof(t_cmd_block));
		ft_bzero(new_block, sizeof(t_cmd_block));
		// DEBUG
		if (((t_token *)now->content)->type != WORD)
			printf("DEBUG : token is not word. build_token_to_cmd_block() : %d\n", ((t_token *)now->content)->type);
		new_block->cmd = (t_token *)now->content;
		now = fill_subcontext_cmd_block(new_block, now->next);
		ft_lstadd_back(out_list_cmd_blocks, ft_lstnew(new_block));
	}
	// DEBUG 
	t_list *p = *out_list_cmd_blocks;
	for (; p != NULL; p = p->next)
	{
		t_cmd_block* now = (t_cmd_block *)p->content;
		printf("cmd.str = %s\n", now->cmd->str);
		printf("cmd.type = %d\n", now->cmd->type);
		printf("num_options = %d\n", now->num_options);
		for (int i = 0; i < now->num_options; i++)
		{
			printf("    %s\n", now->options[i]);
		}
		printf("redirect = %p %d %p %d\n", 
			now->redirect_in, now->redirect_is_heredoc, now->redirect_out, now->redirect_is_append);
		printf("\n\n");
	}
}
