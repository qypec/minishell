/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 05:03:02 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 17:29:17 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				add_quotes_to_stack(t_buff *token, t_list **operator, const char *input_line, int *i)
{
	t_list				*tmp;

	if (*operator != NULL && input_line[*i] != (*operator)->content[0])
		ft_buffaddsymb(token, input_line[(*i)++]);
	else if (*operator != NULL && input_line[*i] == (*operator)->content[0])
	{
		ft_lstdelfirst(operator);
		(*i)++;
	}
	else
	{
		ft_lstadd(operator, ft_lstnew(input_line + (*i)));
		(*i)++;
	}
}

static void				slash_processing(t_buff	*token, const char *input_line, int *i)
{
	if (input_line[*i + 1] != '\0')
	{
		ft_buffaddsymb(token, input_line[*i + 1]);
		(*i) += 2;
	}
	else
		ft_buffaddsymb(token, input_line[(*i)++]);
}

static t_list			*space_processing(t_buff **token, t_list *operator, const char *input_line, int *i)
{
	t_list				*new_token_to_result;

	if (operator != NULL && is_quotes(operator->content[0]))
	{
		while (ft_isspace(input_line[*i]))
			ft_buffaddsymb(*token, input_line[(*i)++]);
		return (NULL);
	}
	new_token_to_result = ft_lstnew((*token)->str);
	ft_buffdel(token);
	*token = ft_buffinit(SCREENING_BUFF_SIZE);
	while (ft_isspace(input_line[*i]))
		(*i)++;
	return (new_token_to_result);
}

static void				end_of_line_processing(t_buff **token, t_list **operator, t_list **result)
{
	if (*operator != NULL && is_quotes((*operator)->content[0]))
		wait_quotes_from_input(*token, *operator, result);
	else
	{
		ft_lstpushback(result, ft_lstnew((*token)->str));
		ft_lstdel(operator);
		ft_buffdel(token);
	}
}

void				screening_loop(const char *input_line, t_buff *token, \
							t_list **result, t_list *operator)
{
	int					i;

	i = 0;
	if (input_line == NULL)
	{
		ft_buffdel(&token);
		return ;
	}
	while (input_line[i] != '\0')
	{
		if (is_quotes(input_line[i]))
			add_quotes_to_stack(token, &operator, input_line, &i);
		else if (input_line[i] == '\\')
			slash_processing(token, input_line, &i);
		else if (input_line[i] == '$' || input_line[i] == '~')
			preprocessing_extension_characters(token, input_line, &i);
		else if (ft_isspace(input_line[i]))
			ft_lstpushback(result, space_processing(&token, operator, input_line, &i));
		else
			ft_buffaddsymb(token, input_line[i++]);
	}
	end_of_line_processing(&token, &operator, result);
}
