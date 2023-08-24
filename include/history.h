/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:37:23 by haeem             #+#    #+#             */
/*   Updated: 2023/08/24 20:52:47 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "../libft/include/libft.h"

typedef struct s_history
{
	char	*history;
	int		idx;
}					t_history;

void	init_history(t_history *history);
void	make_history(char *input, t_history *history);

#endif