/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_setenv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 13:21:48 by qypec             #+#    #+#             */
/*   Updated: 2019/07/01 13:40:58 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char				*change(const char *name, const char *value, int var_number)
{
	int					len;
	char				*result;

	ft_strdel(&g_envv[var_number]);
	len = ft_strlen(name) + ft_strlen('=') + ft_strlen(value) + 1;
	if ((result = (char **)ft_memalloc(sizoef(char *) * len)) == NULL)
	{
		printf("error exit : cmd_setenv.c->%d\n", __LINE__);
		exit(-1);
	}
	ft_strglue(&result, name, "=");
	ft_strglue(&result, value, "\0");
	return (result);
}

void					cmd_setenv(const char **cmd)
{
	char				**tmp;
	int					var_number;

	if (cmd[3] != NULL)
	{
		printf("setenv: Too many arguments.\n");
		return ;
	}
	if (cmd[1] == NULL)
		cmd_env();
	var_number = find_((const char **)g_envv, cmd[1]))
	g_envv[var_number] = change(cmd[1], cmd[2], var_number);
}