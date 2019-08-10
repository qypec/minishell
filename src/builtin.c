/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:51:36 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 13:22:02 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					*is_builtin(const char *builtin_name)
{
	if (builtin_name == NULL)
		return (NULL);
	else if (ft_strcmp("cd", builtin_name) == 0)
		return (&cmd_cd);
	else if (ft_strcmp("echo", builtin_name) == 0)
		return (&cmd_echo);
	else if (ft_strcmp("env", builtin_name) == 0)
		return (&cmd_env);
	else if (ft_strcmp("setenv", builtin_name) == 0)
		return (&cmd_setenv);
	else if (ft_strcmp("unsetenv", builtin_name) == 0)
		return (&cmd_unsetenv);
	return (NULL);
}
