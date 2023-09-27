/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjunk <hyunjunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:42:34 by haeem             #+#    #+#             */
/*   Updated: 2023/09/27 21:54:16 by hyunjunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	malloc_options(t_cmd_block *out_cmd_block)
{
	out_cmd_block->options = (char **)malloc(
			(out_cmd_block->num_options + 1) * sizeof(char *));
	out_cmd_block->options[out_cmd_block->num_options] = NULL;
	if (out_cmd_block->cmd != NULL)
		out_cmd_block->options[0] = out_cmd_block->cmd->str;
	else
		out_cmd_block->options[0] = NULL;
}

//@Argument	:	pos		The position immediately after the cmd.
static void	fill_options_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_list		*pos_origin;
	int			i;

	pos_origin = pos;
	out_cmd_block->num_options = 1;
	while (pos != NULL && ((t_token *)pos->content)->type != PIPE)
	{
		if (((t_token *)pos->content)->type != WORD)
			pos = pos->next;
		else
			out_cmd_block->num_options += 1;
		pos = pos->next;
	}
	malloc_options(out_cmd_block);
	pos = pos_origin;
	i = 1;
	while (pos != NULL && ((t_token *)pos->content)->type != PIPE)
	{
		if (((t_token *)pos->content)->type == WORD)
			out_cmd_block->options[i++] = ((t_token *)pos->content)->str;
		else
			pos = pos->next;
		pos = pos->next;
	}
}

/*
@Arguments 	: pos	The position where the current line stats.

@Return 	: returns the position of the chunk that should be read next. 
			It will be the position of PIPE or NULL. */
static t_list	*fill_redirect_cmd_block(
	t_cmd_block *out_cmd_block, t_list *pos)
{
	t_token		*token;
	t_token		*next_token;
	t_redirect	*new_redirect;
	t_list		*new_node;

	while (pos != NULL && ((t_token *)pos->content)->type != PIPE)
	{
		token = ((t_token *)pos->content);
		if (token->type == WORD)
		{
			pos = pos->next;
			continue ;
		}
		next_token = ((t_token *)pos->next->content);
		new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
		new_redirect->type = token->type;
		new_redirect->str = next_token->str;
		new_node = ft_lstnew(new_redirect);
		if (token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC)
			ft_lstadd_back(&out_cmd_block->redirects_in, new_node);
		else if (token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
			ft_lstadd_back(&out_cmd_block->redirects_out, new_node);
		pos = pos->next->next;
	}
	return (pos);
}

/* @Return 	: The position immediately after the cmd */
static t_list	*fill_cmd_cmd_block(t_cmd_block *out_cmd_block, t_list *pos)
{
	t_token	*token;

	while (pos != NULL)
	{
		token = (t_token *)pos->content;
		if (token->type == PIPE)
			return (pos);
		if (token->type == REDIRECT_IN || token->type == REDIRECT_HEREDOC
			|| token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
			pos = pos->next;
		else if (token->type == WORD)
		{
			out_cmd_block->cmd = token;
			return (pos->next);
		}
		pos = pos->next;
	}
	return (pos);
}

/* It uses shallow copy about strings. 
	The caller should care about this.
	Check the caution in structure comment  */
void	make_cmd_blocks_by_tokens(
	t_list **out_list_cmd_blocks, t_list *list_tokens)
{
	t_list		*start;
	t_list		*next_cmd;
	t_cmd_block	*new_block;
	int			idx;
	char		*tmp;

	*out_list_cmd_blocks = NULL;
	idx = 0;
	start = list_tokens;
	while (start != NULL)
	{
		if (((t_token *)start->content)->type == PIPE)
			start = start->next;
		new_block = (t_cmd_block *)malloc(sizeof(t_cmd_block));
		ft_bzero(new_block, sizeof(t_cmd_block));
		next_cmd = fill_cmd_cmd_block(new_block, start);
		fill_options_cmd_block(new_block, next_cmd);
		start = fill_redirect_cmd_block(new_block, start);
		new_block->idx = idx;
		tmp = ft_itoa(idx);
		new_block->heredoc_file = ft_strjoin(".tmp_heredoc_", tmp);
		free(tmp);
		idx += 1;
		ft_lstadd_back(out_list_cmd_blocks, ft_lstnew(new_block));
	}
}
