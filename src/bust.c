/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bust.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:52:10 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 17:24:59 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						get_errorcode(const char *fullname)
{
	if (access(fullname, EXISTENCE) == -1)
		return (COMMAND_NOT_FOUND);
	else if (access(fullname, IMPLEMENTABILITY) == -1)
		return (PERMISIION_DENIED);
	return (0);
}

int						bust(const char *cmd_name, int error_code)
{
	struct stat		buff;

	if (error_code == 0)
		return (0);
	else if (error_code == COMMAND_NOT_FOUND)
		ft_printf("(mini): command not found : %s\n", cmd_name);
	else if (error_code == NO_SUCH_DIR)
	{
		if (stat(cmd_name, &buff) < 0)
			ft_printf("cd: no such file or directory: %s\n", cmd_name);
		else if (S_ISREG(buff.st_mode))
			ft_printf("cd: not a directory: %s\n", cmd_name);
	}
	else if (error_code == PERMISIION_DENIED)
		ft_printf("minishell: permission denied: %s\n", cmd_name);
	return (1);
}
