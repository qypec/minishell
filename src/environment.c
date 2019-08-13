/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:23:35 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 16:32:07 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					delete_environment_variable(const char *variable)
{
	char				**new_matr;
	size_t				size_of_new_environment;
	int					indexof_var;
	int					i;
	int					j;

	if ((indexof_var = find_((const char **)g_envv, variable)) == -1)
		return ;
	size_of_new_environment = ft_matrlen((const char **)g_envv) - 1;
	if ((new_matr = (char **)malloc(sizeof(char *) * \
					(size_of_new_environment + 1))) == NULL)
		exit(-1);
	new_matr[size_of_new_environment] = NULL;
	i = 0;
	j = -1;
	while (g_envv[++j] != NULL)
	{
		if (j == indexof_var)
			continue ;
		new_matr[i++] = ft_strdup(g_envv[j]);
	}
	ft_matrdel(&g_envv);
	g_envv = new_matr;
	update_envvar_path(variable);
}

void					add_environment_variable(const char *key, const char *value)
{
	char				**new_matr;
	size_t				size_of_new_environment;
	int					i;

	size_of_new_environment = ft_matrlen((const char **)g_envv) + 1; 
	if ((new_matr = (char **)malloc(sizeof(char *) * \
					(size_of_new_environment + 1))) == NULL)
		exit(-1);
	new_matr[size_of_new_environment] = NULL;
	i = 0;
	while (g_envv[i] != NULL)
	{
		new_matr[i] = ft_strdup(g_envv[i]);
		i++;
	}
	if ((new_matr[i] = (char *)ft_memalloc(sizeof(char) * \
		(ft_strlen(key) + ft_strlen("=") + ft_strlen(value) + 1))) == NULL)
		exit(-1);
	ft_strglue(new_matr[i], key, "=", value, NULL);
	ft_matrdel(&g_envv);
	g_envv = new_matr;
	update_envvar_path(key);
}

const char				*getvalue_envv(const char *var_name)
{
	int					indexofkey;
	const char			*result;
	size_t				len;

	if (var_name == NULL)
		return (NULL);
	len = ft_strlen(var_name);
	if ((indexofkey = find_((const char **)g_envv, var_name)) == -1)
		return (NULL);
	result = g_envv[indexofkey] + len + 1;
	return (result);
}

int						find_(const char **envv, const char *var_name)
{
	int					i;
	int					j;
	int					len;

	i = 0;
	while (envv[i] != NULL)
	{
		j = 0;
		len = 0;
		while (envv[i][j] != '=' && envv[i][j] != '\0')
		{
			len++;
			j++;
		}
		if (ft_strncmp(envv[i], var_name, len) == 0 && var_name[len] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
