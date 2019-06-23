/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 16:59:58 by yquaro           ###   ########.fr       */
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
	if ((value = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
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
	if ((key = (char *)ft_memalloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	ft_strncpy(key, envv, len);
	return (key);
}

void					init_envv(const char **envv)
{
	if ((g_envv = ft_matrdup(envv)) == NULL)
	{
		printf("exit error : environment.c->init_env\n");
		exit(-1);
	}
}
