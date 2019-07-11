/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:43:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/11 05:33:55 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				is_forbidden_variable(const char *varname)
{
	if (ft_strcmp(varname, "PATH") == 0)
		return (1);
	return (0);
}

static void				new_genvv(char **tmp, int var_number)
{
	int					i;
	int					j;

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
}

void					cmd_unsetenv(const char *varname)
{
	int					var_number;
	char				**tmp;

	if ((var_number = find_((const char **)g_envv, varname)) == -1)
		return ;
	if (is_forbidden_variable(varname))
	{
		ft_putstr("The variable ");
		ft_putstr(varname);
		ft_putendl(" can not be unset");
		return ;
	}
	tmp = ft_matrdup((const char **)g_envv);
	ft_matrixfree(&g_envv);
	new_genvv(tmp, var_number);
	ft_matrixfree(&tmp);
}
