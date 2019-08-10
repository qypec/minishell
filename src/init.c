/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 13:29:40 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 13:43:16 by yquaro           ###   ########.fr       */
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

void					init_hashtable_from_envvpath(void)
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

static void				setvar_shell(int indexof_shell)
{
	char				dir[PATH_MAX];
	int					size_of_shellvar;

	getcwd(dir, PATH_MAX);
	size_of_shellvar = ft_strlen("SHELL=") + ft_strlen(dir) + ft_strlen("/minishell");
	if ((g_envv[indexof_shell] = (char *)ft_memalloc(sizeof(char) * \
							(size_of_shellvar + 1))) == NULL)
		exit(-1);
	ft_strglue(g_envv[indexof_shell], "SHELL=", dir, "/minishell", NULL);
}

void					init_global_envv(const char **envv)
{
	int					i;

	if ((g_envv = (char **)malloc(sizeof(char *) * (ft_matrlen(envv) + 1))) == NULL)
		exit(-1);
	i = 0;
	while (envv[i] != NULL)
	{
		if (ft_strncmp("SHELL", envv[i], ft_strlen("SHELL")) == 0)
		{
			setvar_shell(i++);
			continue ;
		}
		g_envv[i] = ft_strdup(envv[i]);
		i++;
	}
	g_envv[i] = NULL;
}
