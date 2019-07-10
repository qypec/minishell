/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:12:32 by qypec             #+#    #+#             */
/*   Updated: 2019/07/11 00:50:18 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					manage_tildesign(t_buff *buff)
{
	int					home_number;
	const char			*tmp;
	int					i;

	i = 0;
	home_number = find_((const char **)g_envv, "HOME=");
	tmp = (const char *)(g_envv[home_number] + ft_strlen("HOME="));
	while (tmp[i] != '\0')
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = tmp[i++];
	}
}

void					manage_dollarsign(t_buff *buff, const char *str, int *i)
{
	t_buff				*expan;
	int					var_number;
	int					j;
	const char			*tmp;

	expan = ft_buffinit(15);
	while (ft_isalnum(str[++(*i)]))
	{
		ft_buffreload(expan);
		expan->str[(expan->i)++] = str[*i];
	}
	var_number = find_((const char **)g_envv, expan->str);
	ft_buffdel(&expan);
	if (var_number == -1)
		return ;
	j = 0;
	while (g_envv[var_number][j] != '=')
		j++;
	tmp = (const char *)(g_envv[var_number] + (j + 1));
	j = 0;
	while (tmp[j] != '\0')
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = tmp[j++];
	}
}

void				preprocessoring(t_buff *buff, const char *str, int *i)
{
	if (str[*i] == '~')
	{
		manage_tildesign(buff);
		(*i)++;
	}
	else if (str[*i] == '$')
		manage_dollarsign(buff, str, i);
}
