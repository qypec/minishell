/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 17:36:23 by yquaro           ###   ########.fr       */
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

void				execution(char *fullname, const char **cmd)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
	{
		// signal(SIGINT, handle_ctrl_c);
		if (execve(fullname, (char **)cmd, g_envv) == -1)
			bust(cmd[0], COMMAND_NOT_FOUND);
		g_signalflag = 1;
	}
	else
		wait(&pid);
}

void					check_envpath(const char **cmd)
{
	int					hash;
	char				*fullname;

	if (IS_ABSOLUTE_PATH(cmd[0][0]))
		execution((char *)cmd[0], cmd);
	else
	{
		if ((hash = ft_ismapitem(g_envvpath, cmd[0])) == -1)
		{
			bust(cmd[0], COMMAND_NOT_FOUND);
			return ;
		}
		fullname = get_fullname(cmd[0]);
		execution(fullname, cmd);
		ft_strdel(&fullname);
	}
}
