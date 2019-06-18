/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 03:51:36 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 04:05:19 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int						is_builtin_launch(const char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0)
		cmd_cd();
	else if (ft_strcmp("exit", cmd) == 0)
		cmd_exit();
	else if (ft_strcmp("echo", cmd) == 0)
		cmd_echo();
	else if (ft_strcmp("env", cmd) == 0)
		cmd_env();
	else if (ft_strcmp("setenv", cmd) == 0)
		cmd_setenv();
	else if (ft_strcmp("unsetenv", cmd) == 0)
		cmd_unsetenv();
	else
		return (0);
	return (1);
}
