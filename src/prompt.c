/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 06:09:04 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/12 15:27:29 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					display_git_prompt(char **branch_name)
{
	ft_printf("{green}(mini){magenta} -> (%s){reset} ", *branch_name);
	ft_strdel(branch_name);
}

void					display_default_prompt(void)
{
	ft_printf("{green}(mini){reset} ");
}

void					display_prompt(void)
{
	char				*branch_name;

	if (g_signalflag == 0)
	{
		if ((branch_name = gitdir_search()) != NULL)
			display_git_prompt(&branch_name);
		else
			display_default_prompt();
	}
	else
		g_signalflag = 0;
}
