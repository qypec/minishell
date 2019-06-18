/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 04:58:15 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void					init_envv(const char **envv)
{
	g_envv = NULL;
	char				**new;
	int					i;
	int					len;

	i = 0;
	len = ft_matrlen(envv) + 1 + EXTRA_MEMORY_FOR_SETENV;
	g_envv = (char **)ft_memalloc(sizeof(char *) * len);
	while (envv[i] != NULL)
	{
		g_envv[i] = ft_strdup(envv[i]);
		i++;
	}
	while (i < len)
		g_envv[i++] = NULL;
	g_envvlen = len;
}

void					free_envv(void)
{
	ft_matrixfree(&g_envv);
}

void					check_env_path(const char *line)
{
		
}

