/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 21:44:01 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				error_processing(const char **command)
{
	if (command[2] != NULL)
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
	if ((indexof_pwd = find_(g_envv, "PWD")) == -1)
		add_environment_variable(ft_strjoin("PWD", current_location));
	else
	{
		ft_strdel(&g_envv[indexof_pwd]);
		g_envv[indexof_pwd] = ft_strjoin("PWD=", current_location);
	}
	if ((indexof_oldpwd = find_(g_envv, "OLDPWD")) == -1)
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
	char				*displayed_string;
	size_t				size_of_displayed_string;

	if ((oldpwd_location == getvalue_envv("OLDPWD")) == NULL)
		return (NULL);
	if ((home_path == getvalue_envv("HOME")) == NULL)
		home_path = DEFAULT_HOME_DIR;
	if (ft_strncmp(oldpwd_location, home_path, ft_strlen(home_path)) == 0)
	{
		size_of_displayed_string = ft_strlen("~") + \
						ft_strlen(oldpwd_location + ft_strlen(home_path));
		if ((displayed_string = (char *)ft_memalloc(sizeof(char) * \
						(size_of_displayed_string + 1))) == NULL)
			exit(-1);
		ft_strglue(displayed_string, "~", oldpwd_location + ft_strlen(home_path), NULL);
	}
	else
		displayed_string = ft_strdup(oldpwd_location);
	ft_printf("%s\n", displayed_string);
	return (displayed_string);
}

static char				*get_newpath(const char *path)
{
	char				*newlocation;
	const char			*value_of_home;

	if (ft_strcmp("-", path) == 0)
		return (display_cd_dash());
	else if (ft_strcmp(".", path) == 0)
		return (NULL);
	else if (path == NULL)
	{
		if ((value_of_home = getvalue_envv("HOME")) == NULL)
			return (ft_strdup(DEFAULT_HOME_DIR));
		return (ft_strdup(value_of_home));
	}
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
