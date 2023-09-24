/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_completed_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:17:09 by hyunjunk          #+#    #+#             */
/*   Updated: 2023/09/24 18:42:49 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/hashlib.h"


static char	*find_cwd(char *cmd)
{
	char	*tmp;
	char	*tmp2;
	char	*ret;

	tmp = getcwd(NULL, 0);
	tmp2 = ft_strjoin(tmp, "/");
	ret = ft_strjoin(tmp2, cmd);
	free(tmp);
	free(tmp2);
	if (access(ret, X_OK) == 0)
		return (ret);
	free(ret);
	return (NULL);
}

static char	*find_relative(char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		return (find_cwd(&cmd[2]));
	else if (cmd[0] != '/')
		return (find_cwd(cmd));
	else
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
}

static char	*find_path(char *cmd, char **paths)
{
	char	*tmp;
	char	*ret;

	while (paths != NULL && *paths != NULL)
	{
		tmp = ft_strjoin(*paths, "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, X_OK) == 0)
			return (ret);
		free(ret);
		paths++;
	}
	return (NULL);
}

char	*malloc_find_completed_cmd(t_token *cmd, char **paths)
{
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd->str, '/') != NULL)
		return (find_relative(cmd->str));
	else if (paths != NULL)
		return (find_path(cmd->str, paths));
	else
		return (find_cwd(cmd->str));
}
