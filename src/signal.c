/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 16:48:27 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 15:40:26 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					ctrl_c_tracking(void)
{
	if (g_signalflag == 1)
		g_signalflag = 0;
}

void					handle_ctrl_c(int sig)
{
	sig = 0;
	ft_printf("\n");
	g_signalflag = 0;
	display_prompt();
	g_signalflag = 1;
}
