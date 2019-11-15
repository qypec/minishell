/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 06:09:04 by yquaro            #+#    #+#             */
/*   Updated: 2019/11/15 18:39:27 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Display prompt with git branch
**
** @param 		branch_name
** @return		N/A
*/

void					display_git_prompt(char **branch_name)
{
	ft_printf("{green}(mini){magenta} -> (%s){reset} ", *branch_name);
	ft_strdel(branch_name);
}

/*
** Display prompt without git branch
**
** @param 		N/A
** @return		N/A
*/


void					display_default_prompt(void)
{
	ft_printf("{green}(mini){reset} ");
}

/*
** Display prompt relative to git branch
**
** @param 		N/A
** @return		N/A
*/

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
