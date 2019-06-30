/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/30 22:06:12 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void				collect_executables_to_hashtable(const char **path)
{
	DIR					*dir;
	struct dirent		*entry;

	while (*path != NULL)
	{
		if ((dir = opendir(*path)) == NULL)
		{
			printf("error exit : envpath.c->collect_executables_to_hashtable\n");
			exit(-1);
		}
		while ((entry = readdir(dir)) != NULL)
		{
			if (ft_strcmp((const char *)entry->d_name, ".") == 0 || \
				ft_strcmp((const char *)entry->d_name, "..") == 0)
				continue;
			ft_mapinsert(g_envvpath, (const char *)ft_strdup(entry->d_name), ft_strdup(*path));
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
	{
		printf("error exit : envpath.c->init_htab_envpath\n");
		exit(-1);
	}
	tmp = ft_strsplit(g_envv[pathnumber] + 5, ':');
	collect_executables_to_hashtable((const char **)tmp);
	ft_matrixfree(&tmp);
}

void					check_envpath(const char **cmd)
{
	pid_t			pid;
	int				hash;
	char			*fullname;
	int				len;
	const char		*value;

	if ((pid = fork()) == 0)
	{
		if ((hash = ft_ismapitem(g_envvpath, cmd[0])) == -1)
		{
			bust(cmd[0], COMMAND_NOT_FOUND);
			return ;
		}
		value = ft_getvalue(g_envvpath, cmd[0]);
		len = ft_strlen(cmd[0]) + ft_strlen(value) + 1 + 1;
		fullname = (char *)ft_memalloc(sizeof(char) * len);
		ft_strglue(&fullname, value, "/");
		ft_strglue(&fullname, cmd[0], "\0");
		execve(fullname, (char **)cmd, g_envv);
		ft_strdel(&fullname);
	}
	else
		wait(&pid);
}
