/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screening.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 19:45:43 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/07 06:56:13 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						is_nonscreening_sign(const char *cmd, int i, char sign)
{
	if (i != 0)
	{
		if (cmd[i] == sign && cmd[i - 1] != '\\')
			return (1);
		else
			return (0);
	}
	else if (cmd[i] == sign)
		return (1);
	return (0);
}

static int				is_quotes(char c)
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

static void				parse_quotes(const char *str, int *i, t_list **head)
{
	t_buff				*buff;

	*i += 1;
	buff = NULL;
	buff = init_buff(buff, SCREENING_BUFF_SIZE);
	while ((!is_quotes(str[*i])) && str[*i] != '\0')
	{
		if (buff->i == buff->counter - 1)
			buff = buff_reload(buff, SCREENING_BUFF_SIZE);
		buff->str[buff->i] = str[*i];
		buff->i += 1;
		*i += 1;
	}
	if (is_quotes(str[*i]))
		*i += 1;
	ft_lstpushback(head, ft_lstnew(buff->str));
	buff_del(&buff);
}

char					**screening(const char *str)
{
	int					i;
	t_buff				*buff;
	t_list				*head;

	i = 0;
	head = NULL;
	buff = NULL;
	buff = init_buff(buff, SCREENING_BUFF_SIZE);
	while (str[i] != '\0')
	{
		if (is_quotes(str[i]))
			parse_quotes(str, &i, &head);
		if (str[i] == ' ')
		{
			if (!ft_isempty(buff->str))
				ft_lstpushback(&head, ft_lstnew(buff->str));
			buff_del(&buff);
			buff = init_buff(buff, SCREENING_BUFF_SIZE);
			i++;
			continue ;
		}
		if (buff->i == buff->counter - 1)
			buff = buff_reload(buff, SCREENING_BUFF_SIZE);
		if (str[i] != '\0')
		{
			buff->str[buff->i] = str[i++];
			buff->i += 1;
		}
	}
	if (!ft_isempty(buff->str))
		ft_lstpushback(&head, ft_lstnew(buff->str));
	if (buff != NULL)
		buff_del(&buff);
	return (list_to_matr(&head));
}
