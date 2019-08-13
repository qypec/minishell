/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 22:44:52 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 15:13:53 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					cmd_env(void)
{
	int					i;
	int					j;
	t_buff				*color_var_name;

	i = 0;
	while (g_envv[i] != NULL)
	{
		j = 0;
		color_var_name = ft_buffinit(10);
		ft_buffadd(color_var_name, CYAN_COLOR_CODE);
		while (g_envv[i][j] != '=' && g_envv[i][j] != '\0')
			ft_buffaddsymb(color_var_name, g_envv[i][j++]);
		ft_printf("%s{reset}%s\n", color_var_name->str, g_envv[i++] + j);
		ft_buffdel(&color_var_name);
	}
}
