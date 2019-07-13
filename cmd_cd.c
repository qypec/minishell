/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/13 11:06:26 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				fill_pwd_and_oldpwd(const char *cmd)
{
	int					pwd_number;
	int					oldpwd_number;
	int					len;
	char				dir[PATH_MAX];

	pwd_number = find_((const char **)g_envv, "PWD=");
	oldpwd_number = find_((const char **)g_envv, "OLDPWD=");
	ft_strdel(&g_envv[oldpwd_number]);
	len = ft_strlen("OLDPWD") + ft_strlen(g_envv[pwd_number] + 3) + 1;
	if ((g_envv[oldpwd_number] = \
				(char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&g_envv[oldpwd_number], "OLDPWD", g_envv[pwd_number] + 3);
	ft_strdel(&g_envv[pwd_number]);
	getcwd(dir, PATH_MAX);
	len = ft_strlen("PWD=") + ft_strlen(dir) + \
								ft_strlen("/") + ft_strlen(cmd) + 1;
	if ((g_envv[pwd_number] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&g_envv[pwd_number], "PWD=", dir);
}

void					cmd_cd(const char **cmd)
{
	int					home_number;

	if (cmd[1] == NULL)
	{
		home_number = find_((const char **)g_envv, "HOME=");
		chdir((const char *)g_envv[home_number] + ft_strlen("HOME="));
		fill_pwd_and_oldpwd((const char *)g_envv[home_number] + \
													ft_strlen("HOME="));
		return ;
	}
	if (chdir(cmd[1]) == -1)
	{
		bust(cmd[1], NO_SUCH_DIR);
		return ;
	}
	if (ft_strcmp(cmd[1], ".") != 0)
		fill_pwd_and_oldpwd(cmd[1]);
}
