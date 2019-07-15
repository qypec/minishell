/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/15 21:28:10 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				display_cd_dash(const char *newdir)
{
	const char			*value;
	char				*display;
	int					len;

	if ((value = getvalue_envv("HOME")) == NULL)
		value = DEFAULT_HOME_DIR;
	len = ft_strlen(newdir + ft_strlen(value)) + 1 + 1;
	if ((display = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	display[0] = '~';
	ft_strglue(&display, newdir + ft_strlen(value), "\0");
	ft_putendl(display);
	ft_strdel(&display);
}

static void				update_pwd_and_oldpwd_variables(const char *newpwd, \
											const char *new_oldpwd)
{
	int					indexofpwd;
	int					indexof_oldpwd;
	int					len;

	if ((indexofpwd = find_((const char **)g_envv, "PWD=")) != -1)
	{
		ft_strdel(&g_envv[indexofpwd]);
		len = ft_strlen(newpwd) + ft_strlen("PWD=") + 1;
		if ((g_envv[indexofpwd] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
			exit(-1);
		ft_strglue(&g_envv[indexofpwd], "PWD=", newpwd);
	}
	if ((indexof_oldpwd = find_((const char **)g_envv, "OLDPWD=")) != -1)
	{
		ft_strdel(&g_envv[indexof_oldpwd]);
		len = ft_strlen(new_oldpwd) + ft_strlen("OLDPWD=") + 1;
		if ((g_envv[indexof_oldpwd] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
			exit(-1);
		ft_strglue(&g_envv[indexof_oldpwd], "OLDPWD=", new_oldpwd);
	}
}

static char				*get_userpath(const char *cmd)
{
	char				*new;
	const char			current_dir[PATH_MAX];
	int					len;

	if (IS_ABSOLUTE_PATH(cmd[0]))
		return (ft_strdup(cmd));
	getcwd((char *)current_dir, PATH_MAX);
	len = ft_strlen(current_dir) + ft_strlen("/") + ft_strlen(cmd) + 1;
	if ((new = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&new, current_dir, "/");
	ft_strglue(&new, cmd, "\0");
	return (new);
}

static char				*get_path(const char **cmd)
{
	const char			*value;

	if (cmd[1] == NULL)
	{
		if ((value = getvalue_envv("HOME")) == NULL)
			return (ft_strdup(DEFAULT_HOME_DIR));
		return (ft_strdup(value));
	}
	else if (cmd[1][0] == '-')
	{
		if ((value = getvalue_envv("OLDPWD")) == NULL)
			return (NULL);
		return (ft_strdup(value));
	}
	else if (ft_strcmp(cmd[1], ".") == 0)
		return (NULL);
	return (get_userpath(cmd[1]));
}

void					cmd_cd(const char **cmd)
{
	const char			current_dir[PATH_MAX];
	char				*newdir;

	if (cmd == NULL)
		return ;
	getcwd((char *)current_dir, PATH_MAX);
	if ((newdir = get_path(cmd)) == NULL)
		return ;
	if (chdir(newdir) == -1)
	{
		bust(cmd[1], NO_SUCH_DIR);
		return ;
	}
	if (cmd[1][0] == '-')
		display_cd_dash(newdir);
	update_pwd_and_oldpwd_variables(newdir, current_dir);
	ft_strdel(&newdir);
}
