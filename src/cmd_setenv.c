/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:21:48 by qypec             #+#    #+#             */
/*   Updated: 2019/08/13 18:57:21 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char				*change_envvalue(const char *name, const char *value, \
										int var_number)
{
	int					len;
	char				*result;

	ft_strdel(&g_envv[var_number]);
	len = ft_strlen(name) + ft_strlen("=") + ft_strlen(value) + 1;
	if ((result = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(result, name, "=", value, NULL);
	return (result);
}

static int				error_processing(const char **cmd)
{
	if (cmd[1] != NULL && cmd[2] != NULL && cmd[3] != NULL)
	{
		ft_putendl("setenv: Too many arguments.");
		return (0);
	}
	if (cmd[1] == NULL)
	{
		cmd_env();
		return (0);
	}
	if (ft_alnumstr(cmd[1]) == 0)
	{
		ft_putendl("setenv: Variable name must contain
		 alphanumeric characters.");
		return (0);
	}
	return (1);
}

void					cmd_setenv(const char **cmd)
{
	int					var_number;

	if (error_processing(cmd) == 0)
		return ;
	if ((var_number = find_((const char **)g_envv, cmd[1])) != -1)
	{
		g_envv[var_number] = change_envvalue(cmd[1], cmd[2], var_number);
		update_envvar_path(cmd[1]);
	}
	else
		add_environment_variable(cmd[1], cmd[2]);
}
