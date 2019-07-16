/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/16 14:44:33 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				collect_executables_to_hashtable(const char **path)
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
	int					indexofpath;

	g_envvpath = ft_mapnew(NULL, 2000);
	if ((indexofpath = find_((const char **)g_envv, "PATH=")) == -1)
		return ;
	tmp = ft_strsplit(g_envv[indexofpath] + ft_strlen("PATH="), ':');
	collect_executables_to_hashtable((const char **)tmp);
	ft_matrixfree(&tmp);
}

static char				*get_absolute_bultins_path(const char *str)
{
	int					i;
	char				*buff;
	int					hash;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	if ((buff = (char *)ft_memalloc(sizeof(char) * (i + 1))) == NULL)
		exit(-1);
	ft_strncpy(buff, str, i);
	printf("buff = %s\n", buff);
	if ((hash = ft_ismapitem(g_envvpath, (const char *)buff)) == -1)
		return ((char *)str);
	else
	{
		printf("key = %s\n", g_envvpath->head[hash]->key);
		printf("value = %s\n", g_envvpath->head[hash]->value);
		if (ft_strcmp(g_envvpath->head[hash]->value, buff) == 0)
			return (buff);
		else
			return ((char *)str);
	}
	return (buff);
}

void					check_envpath(const char **cmd)
{
	pid_t			pid;
	char			*fullname;
	const char		*value;
	char			*buff;

	if ((pid = fork()) == 0)
	{
		buff = ft_strdup((char *)cmd[0]);
		if (cmd[0][0] == '/')
			buff = get_absolute_bultins_path(cmd[0]);
		if (ft_ismapitem(g_envvpath, (const char *)buff) == -1)
		{
			bust(cmd[0], COMMAND_NOT_FOUND);
			exit(0);
		}
		ft_strdel((char **)&cmd[0]);
		cmd[0] = buff;
		value = ft_getvalue(g_envvpath, (const char *)buff);
		fullname = (char *)ft_memalloc(sizeof(char) * \
			(ft_strlen(cmd[0]) + ft_strlen(value) + 1 + 1));
		ft_strglue(&fullname, value, "/");
		ft_strglue(&fullname, cmd[0], "\0");
		execve(fullname, (char **)cmd, g_envv);
		ft_strdel(&fullname);
	}
	else
		wait(&pid);
}
