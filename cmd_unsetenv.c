/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:43:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/30 23:22:00 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int				is_forbidden_variable(const char *varname)
{
	if (ft_strcmp(varname, "PATH") == 0)
		return (1);
	// else if (ft_strncmp(varname, NAME_GIT_ENVVAR, \
	// 				ft_strlen(NAME_GIT_ENVVAR) - 1) == 0)
	// 	return (1);
	return (0);
}

void					cmd_unsetenv(const char *varname)
{
	int					var_number;

	if ((var_number = find_((const char **)g_envv, varname)) == -1)
		return ;
	if (is_forbidden_variable(varname))
	{
		printf("The variable %s can not be unset\n", varname);
		return ;
	}
	ft_strdel(&g_envv[var_number]);
}