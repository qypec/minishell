/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/16 18:01:48 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				push_executables_to_hashtable(const char **path)
{
	DIR					*dir;
	struct dirent		*entry;

	while (*path != NULL)
	{
		if ((dir = opendir(*path)) == NULL)
			exit(-1);
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp((const char *)entry->d_name, ".") == 0 || \
				ft_strcmp((const char *)entry->d_name, "..") == 0)
				continue;
			ft_mapinsert(g_envvpath, (const char *)ft_strdup(entry->d_name), \
								ft_strdup(*path));
		}
		closedir(dir);
		path++;
	}
}

void					init_htab_envpath(void)
{
	char				**tmp;
	const char			*envv_path;

	g_envvpath = ft_mapnew(NULL, 2000);
	if ((envv_path = getvalue_envv("PATH")) == NULL)
		return ;
	tmp = ft_strsplit(envv_path, ':');
	push_executables_to_hashtable((const char **)tmp);
	ft_matrixfree(&tmp);
}

const char				*get_builtin_with_absolute_path(const char *cmd)
{
	int					i;
	const char			*builtin;
	int					hash;

	i = ft_strlen(cmd);
	while (cmd[i] != '/')
		i--;
	builtin = cmd + i + 1;
	if ((hash = ft_ismapitem(g_envvpath, builtin)) == -1)
		return (NULL);
	if (ft_strncmp(cmd, ft_getvalue(g_envvpath, builtin), i - 1) == 0)
		return (builtin);
	return (NULL);
}

static char				*get_fullname(const char *builtin)
{
	int					len;
	char				*fullname;
	const char			*value;

	value = ft_getvalue(g_envvpath, builtin);
	len = ft_strlen(value) + ft_strlen("/") + ft_strlen(builtin) + 1;
	if ((fullname = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&fullname, value, "/");
	ft_strglue(&fullname, builtin, "\0");
	return (fullname);
}

void					check_envpath(const char **cmd)
{
	pid_t			pid;
	int				hash;
	char			*fullname;
	const char		*builtin;

	if (IS_ABSOLUTE_PATH(cmd[0][0]))
		builtin = get_builtin_with_absolute_path(cmd[0]);
	else
		builtin = cmd[0];
	if ((hash = ft_ismapitem(g_envvpath, builtin)) == -1)
	{
		bust(cmd[0], COMMAND_NOT_FOUND);
		return ;
	}
	fullname = get_fullname(builtin);
	if ((pid = fork()) == 0)
		execve(fullname, (char **)cmd, g_envv);
	else
		wait(&pid);
	ft_strdel(&fullname);
}
