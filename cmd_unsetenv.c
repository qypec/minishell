/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:43:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/01 12:24:10 by qypec            ###   ########.fr       */
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

static void				new_genvv(char **tmp, int var_number)
{
	int					i;
	int					j;

	if ((g_envv = (char **)malloc(sizeof(char *) * \
				ft_matrlen((const char **)tmp))) == NULL)
	{
		printf("error exit : cmd_unsetenv.c->%d\n", __LINE__);
		exit(-1);
	}
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
	int					len;
	char				**tmp;

	if ((var_number = find_((const char **)g_envv, varname)) == -1)
		return ;
	if (is_forbidden_variable(varname))
	{
		printf("The variable %s can not be unset\n", varname);
		return ;
	}
	tmp = ft_matrdup((const char **)g_envv);
	ft_matrixfree(&g_envv);
	new_genvv(tmp, var_number);

}