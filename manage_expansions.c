/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:12:32 by qypec             #+#    #+#             */
/*   Updated: 2019/07/02 20:36:34 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char				*manage_tildesign(char *result, size_t *size)
{
	int					home_number;

	home_number = find_((const char **)g_envv, "HOME=");
	*size += ft_strlen(g_envv[home_number] + ft_strlen("HOME="));
	if ((result = ft_realloc((void *)result, *size)) == NULL)
	{
		printf("error exit : manage_expansions.c->manage_tildesign\n");
		exit(-1);
	}
	ft_strglue(&result, (const char *)(g_envv[home_number] + ft_strlen("HOME=")), "\0");
	return (result);
}

static char				*manage_dollarsign(const char *cmd, char *result, int *i, size_t *size)
{
	int					len;
	char				*envvar;
	int					var_number;
	int					tmp_i;

	len = *i;
	*i += 1;
	tmp_i = *i;
	while (cmd[*i] != ' ' && cmd[*i] != '\0')
		*i += 1;
	len = *i - len;
	if ((envvar = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
	{
		printf("error exit : manage_expansions.c->manage_dollarsign\n");
		exit(-1);
	}
	ft_strncpy(envvar, cmd + tmp_i, len);
	ft_strglue(&envvar, "=", "\0");
	if ((var_number = find_((const char **)g_envv, envvar)) == -1)
	{
		ft_strdel(&envvar);
		if (ft_strlen(result) == 0)
			return (NULL);
		return (result);
	}
	*size += ft_strlen(g_envv[var_number] + len + 1);
	result = ft_realloc((void *)result, *size);
	ft_strglue(&result, (const char *)(g_envv[var_number] + len), "\0");
	ft_strdel(&envvar);
	return (result);
}

static char				*preprocessoring(char *cmd)
{
	char				*result;
	size_t				size;
	int					i;
	int					j;

	size = ft_strlen(cmd) + 1;
	if ((result = (char *)ft_memalloc(sizeof(char) * size)) == NULL)
	{
		printf("error exit : manage_expansions.c->preprocessoring\n");
		exit(-1);
	}
	j = 0;
	if (cmd[0] == '~')
	{
		result = manage_tildesign(result, &size);
		j = size;
	}
	i = 0;
	while (cmd[i] != '\0')
	{
		if (is_nonscreening_sign((const char *)cmd, i, '$'))
		{
			result = manage_dollarsign((const char *)cmd, result, &i, &size);
			j = ft_strlen(result);
		}
		else if (cmd[i] != '\\')
			result[j++] = cmd[i++];
		else
			i++;
	}
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