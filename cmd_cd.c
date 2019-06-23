/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:03:05 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 20:29:48 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static const char		*find_home(const char **envv)
{
	while (*envv != NULL)
	{
		if (ft_strncmp("HOME", *envv, 4) == 0)
			return (*envv);
		envv++;
	}
	return (NULL);
}

void					cmd_cd(const char **cmd)
{
	if (cmd[1] == NULL)
		chdir(find_home((const char **)g_envv));
	else
	{
		if (chdir(cmd[1]) == -1)
			bust(cmd[1], NO_SUCH_DIR);
	}
}