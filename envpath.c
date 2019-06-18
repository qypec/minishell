/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:25:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 07:02:23 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int				find_pathenv(void)
{
	int					i;

	i = 0;
	while (g_envv[i] != NULL)
	{
		if (ft_strncmp((const char *)g_envv[i], "PATH", 4) == 0)
			return (i);
		i++;
	}
	return (-1);
}

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
			ft_putendl(entry->d_name);
			ft_htabadd(&g_htab, (const char *)entry->d_name, *path);
		}
		closedir(dir);
		path++;
	}

}

void					init_htab_envpath(void)
{
	char				**tmp;
	int					pathnumber;

	g_htab = *ft_htabnew(NULL);
	if ((pathnumber = find_pathenv()) == -1)
		exit(-1);
	// printf("%d\n", pathnumber);
	tmp = ft_strsplit(g_envv[pathnumber] + 5, ':');
	ft_putmatrix(tmp);
	printf("%d\n", ft_hashfunc("afinfo"));
	collect_executables_to_hashtable((const char **)tmp);
	// ft_puthtab(&g_htab);
}
