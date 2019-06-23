/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 15:44:47 by yquaro           ###   ########.fr       */
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
			exit(-1);
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

void					init_htab_envpath(void)
{
	char				**tmp;
	int					pathnumber;

	g_envvpath = ft_mapnew(NULL, 2000);
	pathnumber = ft_ismapitem(g_envv, "PATH");
	tmp = ft_strsplit(g_envv->head[pathnumber]->value, ':');
	collect_executables_to_hashtable((const char **)tmp);
	ft_matrixfree(&tmp);
}
