/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:43:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/09 19:48:38 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				is_forbidden_variable(const char *varname)
{
	if (ft_strcmp(varname, "SHLVL") == 0)
		return (1);
	return (0);
}

static void				new_genvv(int var_number)
{
	int					i;
	int					j;
	char				**tmp;

	tmp = ft_matrdup((const char **)g_envv);
	ft_matrdel(&g_envv);
	if ((g_envv = (char **)malloc(sizeof(char *) * \
				ft_matrlen((const char **)tmp))) == NULL)
		exit(-1);
	i = 0;
	j = 0;
	while (tmp[i] != NULL)
	{
		if (i == var_number)
		{
			i++;
			continue ;
		}
		g_envv[j++] = ft_strdup(tmp[i++]);
	}
	g_envv[j] = NULL;
	ft_matrdel(&tmp);
}

static int				error_processing(const char **cmd)
{
	if (cmd[1] == NULL)
	{
		ft_putendl("unsetenv: Too few arguments.");
		return (0);
	}
	if (is_forbidden_variable(cmd[1]))
	{
		ft_putstr("The variable ");
		ft_putstr(cmd[1]);
		ft_putendl(" can not be unset");
		return (0);
	}
	return (1);
}

void					cmd_unsetenv(const char **cmd)
{
	int					var_number;
	int					i;

	if (error_processing(cmd) == 0)
		return ;
	i = 1;
	while (cmd[i] != NULL)
	{
		if ((var_number = find_((const char **)g_envv, cmd[i])) == -1)
		{
			i++;
			continue ;
		}
		new_genvv(var_number);
		update_envvar_path(cmd[i]);
		i++;
	}
}