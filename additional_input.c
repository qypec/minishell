/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 00:52:03 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/11 01:05:56 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				display_quote_prompt(void)
{
	write(1, "\n", 1);
	write(1, "\x1b[31mquote\x1b[0m -> ", 18);
}

void					wait_quote_from_input(t_buff *buff, char c)
{
	char				symb;

	display_quote_prompt();
	while (read(0, &symb, 1) > 0)
	{
		if (symb == '\n')
		{
			buff->str[(buff->i)++] = '\n';
			display_quote_prompt();
		}
		ft_buffreload(buff);
		buff->str[(buff->i)++] = symb;
		if (symb == c)
			return ;
	}
}
