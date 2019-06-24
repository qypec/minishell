/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/24 20:11:12 by yquaro           ###   ########.fr       */
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
	int					len;
	int					i;
	int					j;
	int					envvlen;

	envvlen = ft_matrlen(envv);
	len = envvlen + 10 + 1;
	g_envvlen = envvlen;
	if ((g_envv = (char **)malloc(sizeof(char *) * len)) == NULL)
	{
		printf("error exit : environment.c->init_envv\n");
		exit(-1);
	}
	add_gitdirpath_to_envv(envv);
	i = 0;
	j = 1;
	while (envv[i] != NULL)
		g_envv[j++] = ft_strdup(envv[i++]);
	while (j < len)
		g_envv[j++] = NULL;
}
