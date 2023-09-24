/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haeem <haeem@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:45:13 by haeem             #+#    #+#             */
/*   Updated: 2023/09/24 18:26:19 by haeem            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// chdir sets errno if fails
static int	cd_dir_changer(t_hashmap *envmap, char *path)
{
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (BUILTIN);
	}
	hashmap_insert(envmap, "PWD", path);
	return (SUCCESS);
}

static int	cd_try_relative_path(t_hashmap *envmap, char **argv)
{
	char	*cwd;
	char	*terminated_path;
	char	*path;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (ft_strcmp(cwd, "/") == 0)
		path = ft_strdup(argv[1]);
	else
	{
		terminated_path = ft_strjoin(cwd, "/");
		path = ft_strjoin(terminated_path, argv[1]);
		free(terminated_path);
	}
	free(cwd);
	terminated_path = NULL;
	cwd = NULL;
	ret = cd_dir_changer(envmap, path);
	free(path);
	return (ret);
}

// try absolute path, if it doesn't exist, try relative path
int	builtin_cd(char **argv, t_hashmap *envmap)
{
	if (argv[1] == NULL)
		return (cd_dir_changer(envmap, hashmap_search(envmap, "HOME")));
	if (argv[1][0] == '/')
		return (cd_dir_changer(envmap, argv[1]));
	else
		return (cd_try_relative_path(envmap, argv));
}
