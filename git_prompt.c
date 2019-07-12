/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:41:37 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/12 19:27:14 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				is_git_envvar_zone()
{
	int					i;

	i = 0;
	while (g_envv[i] != NULL)
	{
		if (ft_strncmp((const char *)g_envv[i], NAME_GIT_ENVVAR, \
					ft_strlen(NAME_GIT_ENVVAR)) == 0)
			return (i);
		i++;
	}
	return (0);
}

char					*is_gitzone(void)
{
	int					varnumber;

	if ((varnumber = is_git_envvar_zone()) != 0)
		return (get_branch_name());
	return (search_gitdir());
}
