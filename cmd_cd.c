/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 23:20:05 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static const int		find_(const char **envv, const char *envvname)
{
	int					i;

	i = 0;
	while (envv[i] != NULL)
	{
		if (ft_strncmp(envvname, envv[i], 3) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static const char		*find_home(const char **envv)
{
	while (*envv != NULL)
	{
		if (ft_strncmp("HOME", *envv, 4) == 0)
			return (*envv);
		envv++;
	}
	return (NULL);
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
	if (cmd[1] == NULL)
		chdir(find_home((const char **)g_envv));
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			bust(cmd[1], NO_SUCH_DIR);
			return ;
		}
	}
	if (ft_strcmp(cmd[1], ".") != 0)
		fill_pwd_and_oldpwd(cmd[1]);
}