/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/27 01:59:07 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int				tilde_treatment(const char *path)
{
	char				*fullpath;
	int					home_number;
	int					len_1;
	int					len;

	home_number = find_((const char **)g_envv, "HOME");
	len = ft_strlen(g_envv[home_number] + ft_strlen("HOME=")) + \
			(ft_strlen(path) - 1);
	if ((fullpath = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
	{
		printf("error exit : cmd_cd.c->tilde_treatment\n");
		exit(-1);
	}
	ft_strglue(&fullpath, g_envv[home_number] + ft_strlen("HOME="), path + 1);
	if (chdir(fullpath) == -1)
	{
		bust(fullpath, NO_SUCH_DIR);
		ft_strdel(&fullpath);
		return (-1);	
	}
	ft_strdel(&fullpath);
	return (0);
}

static void				fill_pwd_and_oldpwd(const char *cmd)
{
	int					pwd_number;
	int					oldpwd_number;
	int					len;
	char				dir[PATH_MAX];

	pwd_number = find_((const char **)g_envv, "PWD");
	oldpwd_number = find_((const char **)g_envv, "OLDPWD");
	ft_strdel(&g_envv[oldpwd_number]);
	len = ft_strlen("OLDPWD") + ft_strlen(g_envv[pwd_number] + 3) + 1;
	if ((g_envv[oldpwd_number] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
	{
		printf("exit error : cmd_cd.c->fill_pwd_and_oldpwd\n");
		exit(-1);
	}
	ft_strglue(&g_envv[oldpwd_number], "OLDPWD", g_envv[pwd_number] + 3);
	ft_strdel(&g_envv[pwd_number]);
	getcwd(dir, PATH_MAX);
	len = ft_strlen("PWD=") + ft_strlen(dir) + ft_strlen("/") + ft_strlen(cmd) + 1;
	if ((g_envv[pwd_number] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
	{
		printf("exit error : cmd_cd.c->fill_pwd_and_oldpwd\n");
		exit(-1);
	}
	ft_strglue(&g_envv[pwd_number], "PWD=", dir);
}

void					cmd_cd(const char **cmd)
{
	int					home_number;

	if (cmd[1] == NULL)
	{
		home_number = find_((const char **)g_envv, "HOME");
		chdir((const char *)g_envv[home_number]);
		return ;
	}
	if (cmd[1][0] == '~' && cmd[1][1] != '~')
	{
		if (tilde_treatment(cmd[1]) == -1)
			return ;
	}
	else if (chdir(cmd[1]) == -1)
	{
		bust(cmd[1], NO_SUCH_DIR);
		return ;
	}
	if (ft_strcmp(cmd[1], ".") != 0)
		fill_pwd_and_oldpwd(cmd[1]);
}