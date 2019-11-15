/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:12:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/11/15 19:47:15 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Completes the shell process
**
** @param 		variables to free
** @return		N/A
*/

void					cmd_exit(char *line, char **level, char **cmd)
{
	ft_strdel(&line);
	ft_matrdel(&level);
	ft_matrdel(&cmd);
	ft_matrdel(&g_envv);
	ft_mapdel(&g_envvpath);
	write(1, "exit\n", 5);
	exit(0);
}
