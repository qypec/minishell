/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 02:07:31 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				error_processing(const char **command)
{
	if (command[1] != NULL && command[2] != NULL)
	{
		ft_printf("cd: string not in pwd: %s\n", command[1]);
		return (1);
	}
	return (0);
}

static void				change_pwd_and_oldpwd_variables(const char *oldpwd_location)
{
	const char			current_location[PATH_MAX];
	int					indexof_pwd;
	int					indexof_oldpwd;

	getcwd((char *)current_location, PATH_MAX);
	if ((indexof_pwd = find_((const char **)g_envv, "PWD")) == -1)
		add_environment_variable(ft_strjoin("PWD", current_location));
	else
	{
		ft_strdel(&g_envv[indexof_pwd]);
		g_envv[indexof_pwd] = ft_strjoin("PWD=", current_location);
	}
	if ((indexof_oldpwd = find_((const char **)g_envv, "OLDPWD")) == -1)
		add_environment_variable(ft_strjoin("OLDPWD", oldpwd_location));
	else
	{
		ft_strdel(&g_envv[indexof_oldpwd]);
		g_envv[indexof_oldpwd] = ft_strjoin("OLDPWD=", oldpwd_location);
	}
}

static char				*display_cd_dash(void)
{
	const char			*oldpwd_location;
	const char			*home_path;

	if ((oldpwd_location = getvalue_envv("OLDPWD")) == NULL)
		return (NULL);
	if ((home_path = getvalue_envv("HOME")) == NULL)
		home_path = DEFAULT_HOME_DIR;
	if (ft_strncmp(oldpwd_location, home_path, ft_strlen(home_path)) == 0)
		ft_printf("~%s\n", oldpwd_location + ft_strlen(home_path));
	else
		ft_printf("%s\n", oldpwd_location);
	return (ft_strdup(oldpwd_location));
}

static char				*get_newpath(const char *path)
{
	char				*newlocation;
	const char			*value_of_home;

	if (ft_isempty(path))
	{
		if ((value_of_home = getvalue_envv("HOME")) == NULL)
			return (ft_strdup(DEFAULT_HOME_DIR));
		return (ft_strdup(value_of_home));
	}
	else if (ft_strcmp("-", path) == 0)
		return (display_cd_dash());
	else if (ft_strcmp(".", path) == 0)
		return (NULL);
	else
		return (ft_strdup(path));
}

void					cmd_cd(const char **command)
{
	const char			oldpwd_location[PATH_MAX];
	char				*newlocation;

	if (error_processing(command))
		return ;
	getcwd((char *)oldpwd_location, PATH_MAX);
	if ((newlocation = get_newpath(command[1])) == NULL)
		return ;
	if (chdir(newlocation) == -1)
		bust(command[1], NO_SUCH_DIR);
	else
		change_pwd_and_oldpwd_variables(oldpwd_location);
	ft_strdel(&newlocation);
}
