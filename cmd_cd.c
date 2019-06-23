/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 22:41:08 by yquaro           ###   ########.fr       */
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

void					cmd_cd(const char **cmd)
{
	int					pwd_number;
	int					oldpwd_number;

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
	pwd_number = find_((const char **)g_envv, "PWD");
	oldpwd_number = find_((const char **)g_envv, "OLDPWD");
	ft_strdel(&g_envv[oldpwd_number]);
	g_envv[oldpwd_number] = ft_strdup(g_envv[pwd_number]);
	ft_strdel(&g_envv[pwd_number]);
	g_envv[pwd_number] = ft_strdup(cmd[1]);
}