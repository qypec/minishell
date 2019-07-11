/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:45:43 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/11 04:10:48 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				is_quotes(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static int				is_expansion_sign(char c)
{
	if (c == '$' || c == '~')
		return (1);
	return (0);	
}

static char				**list_to_matr(t_list **head)
{
	t_list				*tmp;
	int					len;
	char				**matr;
	int					i;

	if (*head == NULL)
		return (NULL);
	len = ft_listsize(*head);
	if ((matr = (char **)malloc(sizeof(char *) * (len + 1))) == NULL)
		exit(-1);
	tmp = *head;
	i = 0;
	while (i < len)
	{
		matr[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	matr[i] = NULL;
	ft_lstdel(head);
	return (matr);
}

static void				work_with_call_stack(t_buff *buff, t_list **oper, const char *str, int *i)
{
	t_list				*tmp;

	if (*oper != NULL && str[*i] != (*oper)->content[0])
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = str[(*i)++];
		return ;
	}
	else if (*oper != NULL && str[*i] == (*oper)->content[0])
	{
		tmp = *oper;
		*oper = (*oper)->next;
		default_lstdel(tmp);
		(*i)++;
		return ;
	}
	if ((tmp = (t_list *)malloc(sizeof(t_list))) == NULL)
		exit(-1);
	tmp->next = NULL;
	if ((tmp->content = (char *)ft_memalloc(sizeof(char) * 2)) == NULL)
		exit(-1);
	tmp->content[0] = str[*i];
	tmp->content[1] = '\0';
	ft_lstadd(oper, tmp);
	(*i)++;
}

static void				slash_processing(t_buff	*buff, const char *str, int *i)
{
	if (str[*i + 1] != '\0')
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = str[*i + 1];
		(*i)++;
	}
	else
	{
		ft_buffreload(buff);
		buff->str[(buff->i)++] = str[(*i)++];
	}
}

static t_list			*space_processing(t_buff **buff, t_list *oper, const char *str, int *i)
{
	t_list				*new;

	if (oper != NULL && is_quotes(oper->content[0]))
	{
		while (ft_isspace(str[*i]))
		{
			ft_buffreload(*buff);
			(*buff)->str[((*buff)->i)++] = str[(*i)++];
		}
		return (NULL);
	}
	if (!ft_isempty(str))
	{
		if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
			exit(-1);
		new->next = NULL;
		new->content = ft_strdup((*buff)->str);
	}
	ft_buffdel(buff);
	*buff = ft_buffinit(SCREENING_BUFF_SIZE);
	while (ft_isspace(str[*i]))
		(*i)++;
	return (new);
}

static void				end_of_string(t_buff **buff, t_list **oper, t_list **result)
{
	t_list				*tmp;
	t_list				*new;

	tmp = *oper;
	if (tmp != NULL && is_quotes(tmp->content[0]))
	{
		wait_quote_from_input(*buff, *oper, result);
		return ;
	}
	if (*oper != NULL)
		ft_lstdel(oper);
	if ((new = (t_list *)malloc(sizeof(t_list))) == NULL)
		exit(-1);
	new->next = NULL;
	if ((new->content = (char *)ft_memalloc(sizeof(char) * ((*buff)->i + 1))) == NULL)
		exit(-1);
	ft_strncpy(new->content, (*buff)->str, (*buff)->i);
	ft_buffdel(buff);
	ft_lstpushback(result, new);
}

void				screening_loop(const char *str, t_buff *buff, t_list **result, t_list *oper)
{
	int					i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_quotes(str[i]))
			work_with_call_stack(buff, &oper, str, &i);
		else if (str[i] == '\\')
			slash_processing(buff, str, &i);
		else if (is_expansion_sign(str[i]))
			preprocessoring(buff, str, &i);
		else if (ft_isspace(str[i]))
			ft_lstpushback(result, space_processing(&buff, oper, str, &i));
		else
		{
			ft_buffreload(buff);
			buff->str[(buff->i)++] = str[i++];
		}
	}
	end_of_string(&buff, &oper, result);
}

char					**screening(const char *str)
{
	t_list				*result;
	t_buff				*buff;
	t_list				*oper;

	buff = ft_buffinit(SCREENING_BUFF_SIZE);
	oper = NULL;
	result = NULL;
	screening_loop(str, buff, &result, oper);
	// if (buff != NULL)
	// 	ft_buffdel(&buff);
	// if (oper != NULL)
	// 	ft_lstdel(&oper);
	return (list_to_matr(&result));
}
