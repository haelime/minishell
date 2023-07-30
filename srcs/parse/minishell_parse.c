/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 18:48:50 by haeem             #+#    #+#             */
/*   Updated: 2023/07/30 20:32:18 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../libft/include/libft.h"

// parse, tokenize, make abstract syntax tree, expand to execute
void	parse(t_cmd *cmd, char *line)
{
	char	**tmp;
	int		i;

	i = 0;
	line = readline(PROMPT);
	if (!line)
		exit(0);
	add_history(line);
	tmp = ft_split(line, ' ');
	cmd->cmd = tmp[0];
	while (tmp[i])
		i++;
	cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (tmp[i])
	{
		cmd->argv[i] = tmp[i];
		i++;
	}
	cmd->argv[i] = NULL;
	free(line);
	free(tmp);
}

