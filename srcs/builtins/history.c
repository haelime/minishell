/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:17:13 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 20:54:08 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/history.h"

void	init_history(t_history *history)
{
	history->history = ft_strdup("    ");
	history->idx = 1;
}

void	make_history(char *input, t_history *history)
{
	if (input)
	{
		if (history->idx != 1)
			history->history = ft_strjoin(history->history, "    ");
		history->history = \
			ft_strjoin(history->history, ft_itoa(history->idx));
		history->history = \
			ft_strjoin(history->history, " ");
		history->history = \
			ft_strjoin(history->history, input);
		history->history = \
			ft_strjoin(history->history, "\n");
		history->idx++;
	}
}

// for arrow up and down
char	*get_history(t_history *history, int idx)
{
	char	**history_arr;
	char	*ret;
	int		i;

	i = 0;
	history_arr = ft_split(history->history, '\n');
	while (history_arr[i])
		i++;
	if (idx > i)
		return (NULL);
	ret = ft_strdup(history_arr[i - idx]);
	ft_free_strings(history_arr);
	return (ret);
}

// builtin history
void	print_history(t_history *history)
{
	printf("%s", history->history);
}
