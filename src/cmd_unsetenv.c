/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unsetenv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 22:43:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 14:40:16 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				is_forbidden_variable(const char *varname)
{
	if (ft_strcmp(varname, "SHLVL") == 0)
		return (1);
	return (0);
}

static int				error_processing(const char **command)
{
	int					i;

	if (command[1] == NULL)
	{
		ft_putendl("unsetenv: Too few arguments.");
		return (0);
	}
	i = 1;
	while (command[i] != NULL)
	{
		if (is_forbidden_variable(command[i]))
		{
			ft_printf("The variable %s can not be unset", command[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void					cmd_unsetenv(const char **command)
{
	int					i;

	if (error_processing(command) == 0)
		return ;
	i = 1;
	while (command[i] != NULL)
		delete_environment_variable(command[i++]);
}
