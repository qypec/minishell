/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 22:44:52 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 13:10:45 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					cmd_env(void)
{
	int					i;

	i = 0;
	while (g_envv[i] != NULL)
		ft_printf("%s\n", g_envv[i++]);
}
