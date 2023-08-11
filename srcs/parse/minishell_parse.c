/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/08/09 17:35:28 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/astreelib.h"
#include "../../libft/include/libft.h"

// parse, tokenize, make abstract syntax tree, expand to execute
// void	parse(char *line)
// {
// 	t_lst	*chunks;
// 	t_ast	*syntax;

// 	get_line(&line);
// 	chunks = tokenize(line);
// 	syntax = astree(chunks);
// 	expand(syntax);
// }

