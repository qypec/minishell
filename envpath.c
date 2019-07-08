/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/07 06:55:41 by yquaro           ###   ########.fr       */
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

static int				find_path(const char **envv)
{
	int					i;

	i = 0;
	while (envv[i] != NULL)
	{
		if (ft_strncmp("PATH", envv[i], 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void					init_htab_envpath(void)
{
	char				**tmp;
	int					pathnumber;

	g_envvpath = ft_mapnew(NULL, 2000);
	if ((pathnumber = find_path((const char **)g_envv)) == -1)
		exit(-1);
	tmp = ft_strsplit(g_envv[pathnumber] + 5, ':');
	collect_executables_to_hashtable((const char **)tmp);
	ft_matrixfree(&tmp);
}

static char				*get_name(const char *str)
{
	int					len;
	int					i;
	char				*buff;

	i = ft_strlen(str);
	len = 0;
	while (str[--i] != '/')
		len++;
	if ((buff = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		exit(-1);
	len = 0;
	while (str[++i] != '\0')
		buff[len++] = str[i];
	buff[len] = '\0';
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
			buff = get_name(cmd[0]);
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
