/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bust.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:52:10 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 20:12:42 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void					bust(const char *cmd_name, int flag)
{
	if (flag == COMMAND_NOT_FOUND)
	{
		ft_putstr("[0;31m(mini): command not found : ");
		ft_putendl(cmd_name);
	}
	else if (flag == NO_SUCH_DIR)
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(cmd_name);
	}
}