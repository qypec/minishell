/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:21:48 by qypec             #+#    #+#             */
/*   Updated: 2019/07/07 06:39:11 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				check_alphanumeric_characters(const char *varname)
{
	int					i;

	i = 0;
	while (varname[i] != '\0')
	{
		if (!ft_isalnum(varname[i]))
			return (0);
		i++;
	}
	return (1);
}

static void				new_genvv(char **tmp, const char *name, \
										const char *value)
{
	int					i;
	int					len;

	if ((g_envv = (char **)malloc(sizeof(char *) * \
			(ft_matrlen((const char **)tmp) + 1 + 1))) == NULL)
		exit(-1);
	i = -1;
	while (tmp[++i] != NULL)
		g_envv[i] = ft_strdup(tmp[i]);
	len = ft_strlen(name) + ft_strlen("=") + ft_strlen(value) + 1;
	if ((g_envv[i] = (char *)ft_memalloc(sizeof(char *) * len)) == NULL)
		exit(-1);
	ft_strglue(&g_envv[i], name, "=");
	ft_strglue(&g_envv[i], value, "\0");
	g_envv[i + 1] = NULL;
}

static char				*change(const char *name, const char *value, \
										int var_number)
{
	int					len;
	char				*result;

	ft_strdel(&g_envv[var_number]);
	len = ft_strlen(name) + ft_strlen("=") + ft_strlen(value) + 1;
	if ((result = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
		exit(-1);
	ft_strglue(&result, name, "=");
	ft_strglue(&result, value, "\0");
	return (result);
}

void					cmd_setenv(const char **cmd)
{
	char				**tmp;
	int					var_number;

	if (cmd[1] != NULL && cmd[2] != NULL && cmd[3] != NULL)
	{
		ft_putendl("setenv: Too many arguments.");
		return ;
	}
	if (cmd[1] == NULL)
	{
		cmd_env();
		return ;
	}
	if (check_alphanumeric_characters(cmd[1]) == 0)
	{
		ft_putendl("setenv: Variable name must contain alphanumeric characters.");
		return ;
	}
	if ((var_number = find_((const char **)g_envv, cmd[1])) != -1)
	{
		g_envv[var_number] = change(cmd[1], cmd[2], var_number);
		return ;
	}
	tmp = ft_matrdup((const char **)g_envv);
	ft_matrixfree(&g_envv);
	new_genvv(tmp, cmd[1], cmd[2]);
	ft_matrixfree(&tmp);
}
