/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:12:32 by qypec             #+#    #+#             */
/*   Updated: 2019/08/13 18:54:20 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				manage_tildesign(t_buff *token)
{
	const char			*home_value;

	if ((home_value = getvalue_envv("HOME")) == NULL)
		ft_buffadd(token, DEFAULT_HOME_DIR);
	ft_buffadd(token, home_value);
}

static void				manage_dollarsign(t_buff *token, \
									const char *input_line, int *i)
{
	t_buff				*var_name;

	var_name = ft_buffinit(15);
	while (ft_isalnum(input_line[++(*i)]))
		ft_buffaddsymb(var_name, input_line[*i]);
	if (!ft_isspace(input_line[(*i)]) && input_line[(*i)] != '\0')
		ft_buffaddsymb(token, '$');
	ft_buffadd(token, getvalue_envv(var_name->str));
	ft_buffdel(&var_name);
}

void					preprocessing_extension_characters(t_buff *token, \
										const char *input_line, int *i)
{
	if (input_line[*i] == '~')
	{
		manage_tildesign(token);
		(*i)++;
	}
	else if (input_line[*i] == '$')
		manage_dollarsign(token, input_line, i);
}
