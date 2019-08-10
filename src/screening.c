/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:45:43 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/10 11:31:50 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						is_quotes(char c)
{
	if (c == '\'' || c == '\"')
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

char					**screening(const char *input_line)
{
	t_list				*result;
	t_buff				*token;
	t_list				*operator;

	operator = NULL;
	result = NULL;
	token = ft_buffinit(SCREENING_BUFF_SIZE);
	screening_loop(input_line, token, &result, operator);
	return (list_to_matr(&result));
}
