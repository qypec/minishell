/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 16:30:51 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					update_envvar_path(const char *cmd)
{
	if (ft_strcmp(cmd, "PATH") == 0)
	{
		ft_mapdel(&g_envvpath);
		init_hashtable_from_envvpath();
	}
}

void				execution(const char *fullname, const char **cmd)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
	{
		if (execve(fullname, (char **)cmd, g_envv) == -1)
			bust(cmd[0], COMMAND_NOT_FOUND);
	}
	else
		wait(&pid);
}

void					launch_executable_from_this_directory(const char **command)
{
	const char			current_dir[PATH_MAX];
	const char			*fullname;

	getcwd((char *)current_dir, PATH_MAX);
	fullname = current_dir;
	ft_strglue((char *)fullname, command[0] + 1, NULL);
	execution(fullname, command);
}

static char				*get_fullname(const char *builtin)
{
	int					len;
	char				*fullname;
	const char			*value;

	value = ft_mapvalue(g_envvpath, builtin);
	len = ft_strlen(value) + ft_strlen("/") + ft_strlen(builtin) + 1;
	if ((fullname = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(fullname, value, "/", builtin, NULL);
	return (fullname);
}

void					launch_executable(const char **command)
{
	int					hash;
	char				*fullname;

	if (command[0][0] == '.')
		launch_executable_from_this_directory(command);
	else if (IS_ABSOLUTE_PATH(command[0][0]))
		execution(command[0], command);
	else
	{
		if ((hash = ft_ismapitem(g_envvpath, command[0])) == -1)
		{
			bust(command[0], COMMAND_NOT_FOUND);
			return ;
		}
		fullname = get_fullname(command[0]);
		execution(fullname, command);
		ft_strdel(&fullname);
	}
}
