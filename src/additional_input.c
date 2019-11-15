/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 00:52:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/11/15 20:03:36 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Makes screening until a quote is entered by the user.
**
** @param 		N/A
** @return		N/A
*/

static void				display_quote_prompt(void)
{
	ft_printf("{red}quote ->{reset} ");
}

static void				read_loop(t_buff *buff)
{
	int					ret;
	char				symb;

	while ((ret = read(0, &symb, 1)) > 0 && symb != '\n')
		ft_buffaddsymb(buff, symb);
	if (ret == END_OF_FILE)
		read_loop(buff);
}

void					wait_quotes_from_input(t_buff *token, \
									t_list *operator, t_list **result)
{
	t_buff				*new;

	display_quote_prompt();
	new = ft_buffinit(SCREENING_BUFF_SIZE);
	ft_buffaddsymb(token, '\n');
	read_loop(new);
	screening_loop((const char *)new->str, token, result, operator);
	ft_buffdel(&new);
}
