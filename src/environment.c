/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/07 15:37:54 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				set_shellvar(int i)
{
	char				dir[PATH_MAX];
	int					len;

	getcwd(dir, PATH_MAX);
	len = ft_strlen("SHELL=") + ft_strlen(dir) + ft_strlen("/minishell") + 1;
	if ((g_envv[i] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(g_envv[i], "SHELL=", dir, "/minishell", NULL);
}

const char				*getvalue_envv(const char *key)
{
	char				*tmp;
	int					indexofkey;
	const char			*result;
	size_t				len;

	if (key == NULL)
		return (NULL);
	len = ft_strlen(key) + 2;
	if ((tmp = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(tmp, key, "=", NULL);
	if ((indexofkey = find_((const char **)g_envv, tmp)) == -1)
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	result = g_envv[indexofkey] + (len - 1);
	ft_strdel(&tmp);
	return (result);
}

int						find_(const char **envv, const char *envvname)
{
	int					i;
	int					len;

	i = 0;
	len = ft_strlen(envvname);
	while (envv[i] != NULL)
	{
		if (ft_strncmp(envv[i], envvname, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void					init_envv(const char **envv)
{
	int					len;
	int					i;

	len = ft_matrlen(envv) + 1;
	if ((g_envv = (char **)malloc(sizeof(char *) * len)) == NULL)
		exit(-1);
	i = 0;
	while (envv[i] != NULL)
	{
		if (ft_strncmp("SHELL", envv[i], ft_strlen("SHELL")) == 0)
		{
			set_shellvar(i++);
			continue ;
		}
		g_envv[i] = ft_strdup(envv[i]);
		i++;
	}
	g_envv[i] = NULL;
}
