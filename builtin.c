/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:51:36 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 20:28:11 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int						is_builtin_launch(const char **cmd)
{
	if (ft_strcmp("cd", cmd[0]) == 0)
		cmd_cd(cmd);
	else if (ft_strcmp("exit", cmd[0]) == 0)
		return (-1);
	// else if (ft_strcmp("echo", cmd[0]) == 0)
	// 	cmd_echo(cmd);
	// else if (ft_strcmp("env", cmd[0]) == 0)
	// 	cmd_env(cmd);
	// else if (ft_strcmp("setenv", cmd[0]) == 0)
	// 	cmd_setenv(cmd);
	// else if (ft_strcmp("unsetenv", cmd[0]) == 0)
	// 	cmd_unsetenv(cmd);
	return (0);
}
