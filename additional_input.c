/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 00:52:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/11 04:59:45 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				display_quote_prompt(void)
{
	write(1, "\x1b[31mquote ->\x1b[0m ", 18);
}

void					wait_quote_from_input(t_buff *buff, t_list *oper, t_list **result)
{
	char				symb;
	t_buff				*new;

	display_quote_prompt();
	new = ft_buffinit(SCREENING_BUFF_SIZE);
	ft_buffreload(buff);
	buff->str[(buff->i)++] = '\n';
	while (read(0, &symb, 1) > 0)
	{
		if (symb == '\n')
			break ;
		ft_buffreload(new);
		new->str[(new->i)++] = symb;
	}
	screening_loop((const char *)new->str, buff, result, oper);
	ft_buffdel(&new);
}
