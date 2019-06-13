/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/13 22:52:09 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void					init_envv(const char **envv)
{
	g_envv = NULL;
	g_envv = ft_matrdup(envv); // мб стоит выделить побольше памяти чем надо изначально для setenv
}

void					free_envv(void)
{
	ft_matrixfree(&g_envv);
}

// void					check_env_path(const char *line)
// {
	
// }

