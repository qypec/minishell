/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 06:09:04 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/13 08:18:51 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					display_git_prompt(char **branch_name)
{
	write(1, "\033[0;32m(mini)\x1b[35m -> (", 23);
	write(1, *branch_name, ft_strlen(*branch_name));
	write(1, ")\x1b[0m ", 6);
	ft_strdel(branch_name);
}

void					display_default_prompt(void)
{
	write(1, "\033[0;32m(mini)\033[0m ", 19);
}

void					display_prompt(void)
{
	char				*branch_name;

	if ((branch_name = is_gitzone()) != NULL)
		display_git_prompt(&branch_name);
	else
		display_default_prompt();
}
