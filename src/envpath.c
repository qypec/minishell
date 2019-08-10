/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 13:13:37 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				push_executables_to_hashtable(const char **path)
{
	DIR					*dir;
	struct dirent		*entry;
	int					i;

	i = 0;
	while (path[i] != NULL)
	{
		if ((dir = opendir(path[i])) == NULL)
			exit(-1);
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp((const char *)entry->d_name, ".") == 0 || \
				ft_strcmp((const char *)entry->d_name, "..") == 0)
				continue;
			ft_mapinsert(g_envvpath, (const char *)ft_strdup(entry->d_name), \
								ft_strdup(path[i]));
		}
		closedir(dir);
		i++;
	}
}

void					init_htab_envvpath(void)
{
	char				**tmp;
	const char			*envv_path;

	g_envvpath = ft_mapnew(NULL, 2000);
	if ((envv_path = getvalue_envv("PATH")) == NULL)
		return ;
	tmp = ft_strsplit(envv_path, ':');
	push_executables_to_hashtable((const char **)tmp);
	ft_matrdel(&tmp);
}

void					update_envvar_path(const char *cmd)
{
	if (ft_strcmp(cmd, "PATH") == 0)
	{
		ft_mapdel(&g_envvpath);
		init_htab_envvpath();
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
		if (execve(fullname, (char **)cmd, g_envv) == -1)
			bust(cmd[0], COMMAND_NOT_FOUND);
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
