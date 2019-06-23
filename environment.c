/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 13:18:15 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char				*get_value(const char *envv)
{
	int					i;
	int					len;
	int					start;
	char				*value;

	i = 0;
	len = 0;
	while (envv[i] != '=' && envv[i] != '\0')
		i++;
	start = ++i;
	while (envv[i++] != '\0')
		len++;
	value = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (envv[start] != '\0')
		value[i++] = envv[start++];
	value[i] = '\0';
	return (value);
}

static char				*get_key(const char *envv)
{
	int					i;
	int					len;
	char				*key;

	i = 0;
	len = 0;
	while (envv[i] != '=' && envv[i] != '\0')
	{
		len++;
		i++;
	}
	key = (char *)malloc(sizeof(char) * (len + 1));
	ft_strncpy(key, envv, len);
	return (key);
}

void					init_envv(const char **envv)
{
	char				*key;
	char				*value;

	g_envv = ft_mapnew(NULL, 100);
	while (*envv != NULL)
	{
		key = get_key(*envv);
		value = get_value(*envv);
		ft_mapinsert(g_envv, key, value);
		envv++;
	}
}

// void					check_env_path(const char *line)
// {
		
// }

