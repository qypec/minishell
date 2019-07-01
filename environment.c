/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/01 20:31:13 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void				set_shellvar(int i)
{
	char				dir[PATH_MAX];
	int					len;

	getcwd(dir, PATH_MAX);
	len = ft_strlen("SHELL=") + ft_strlen(dir) + ft_strlen("/minishell") + 1;
	if ((g_envv[i] = (char *)ft_memalloc(sizeof(char) * len)) == NULL)
	{
		printf("error exit : environment.c->%d\n", __LINE__);
		exit(-1);
	}
	ft_strglue(&g_envv[i], "SHELL=", dir);
	ft_strglue(&g_envv[i], "/minishell", "\0");
}

int						find_(const char **envv, const char *envvname)
{
	int					i;
	int					len;

	i = 0;
	len = ft_strlen(envvname);
	while (envv[i] != NULL)
	{
		if (ft_strncmp(envv[i], envvname, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

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
	len = envvlen + 1 + 1; // gitditpath_envv = +1
	if ((g_envv = (char **)malloc(sizeof(char *) * len)) == NULL)
	{
		printf("error exit : environment.c->init_envv\n");
		exit(-1);
	}
	add_gitdirpath_to_envv(envv);
	i = 0;
	j = 1;
	while (envv[i] != NULL)
	{
		if (ft_strncmp("SHELL", envv[i], ft_strlen("SHELL")) == 0)
		{
			set_shellvar(j++);
			i++;
			continue ;
		}
		g_envv[j++] = ft_strdup(envv[i++]);
	}
	while (j < len)
		g_envv[j++] = NULL;
}
