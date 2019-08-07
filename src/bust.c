/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bust.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:52:10 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/07 06:57:55 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					bust(const char *cmd_name, int flag)
{
	struct stat		buff;

	if (flag == COMMAND_NOT_FOUND)
	{
		ft_putstr("(mini): command not found : ");
		ft_putendl(cmd_name);
	}
	else if (flag == NO_SUCH_DIR)
	{
		if (stat(cmd_name, &buff) < 0)
			ft_putstr("cd: no such file or directory: ");
		else if (S_ISREG(buff.st_mode))
			ft_putstr("cd: not a directory: ");
		ft_putendl(cmd_name);
	}
}
