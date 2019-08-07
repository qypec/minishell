/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:12:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/07 15:42:32 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
