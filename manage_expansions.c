/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:12:32 by qypec             #+#    #+#             */
/*   Updated: 2019/06/27 04:11:43 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char				*manage_tildesign(char *result, int *size)
{
	int					home_number;

	home_number = find_((const char **)g_envv, "HOME");
	*size += ft_strlen(g_envv[home_number] + ft_strlen("HOME="));
	if ((result = ft_realloc((void *)result, *size)) == NULL)
	{
		printf("error exit : manage_expansions.c->manage_tildesign\n");
		exit(-1);
	}
	ft_strglue(&result, (const char *)(g_envv[home_number] + ft_strlen("HOME=")), "\0");
	return (result);
}

static char				*manage_dollarsign(char *result, int i, int *size)
{
	int					len;
	int					tmp_i;
	char				*envvar;
	int					envvar_number;

	tmp_i = i + 1;
	len = 0;
	while (result[++i] != ' ' && result[i] != '\0')
		len++;
	if ((envvar = (char *)malloc(sizeof(char *) * (len + 1))) == NULL)
	{
		printf("error exit : manage_expansions.c->manage_dollarsign\n");
		exit(-1);
	}
	ft_strncpy(envvar, (const char *)(result + tmp_i), len);
	if ((envvar_number = find_((const char **)g_envv, envvar)) == -1)
	{
		ft_strdel(&envvar);
		return (result);
	}
	*size += ft_strlen(g_envv[envvar_number] + len + 1);
	if ((result = ft_realloc((void *)result, *size)) == NULL)
	{
		printf("error exit : manage_expansions.c->manage_dollarsign\n");
		exit(-1);
	}
	ft_strglue(&result, envvar, "\0");
	ft_strdel(&envvar);
	return (result);
}

static char				*preprocessoring(char *cmd)
{
	char				*result;
	int					i;
	int					j;
	int					*len;

	*len = ft_strlen(cmd);
	if ((result = (char *)ft_memalloc(sizeof(char) * (*len + 1))) == NULL)
	{
		printf("error exit : manage_expansions.c->preprocessoring\n");
		exit(-1);
	}
	i = 0;
	j = 0;
	if (cmd[0] == '~')
	{
		result = manage_tildesign(result, len);
		j = ft_strlen(result);
		i++;
	}
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
		{
			result = manage_dollarsign(result, i++, len);
			j = ft_strlen(result);
		}
		else
			result[j++] = cmd[i++];
	}
	ft_strdel(&cmd);
	return (result);
}

static int				contains_expansions(const char *cmd)
{
	int					i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' || cmd[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char					**manage_expansions(char **cmd)
{
	int					i;

	i = 1;
	while (cmd[i] != NULL)
	{
		if (contains_expansions((const char *)cmd[i]))
			cmd[i] = preprocessoring(cmd[i]);
		i++;
	}
	return (cmd);
}