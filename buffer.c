/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 18:35:28 by yquaro            #+#    #+#             */
/*   Updated: 2019/07/07 06:54:19 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_buff					*init_buff(t_buff *buff, int size)
{
	if ((buff = (t_buff *)malloc(sizeof(t_buff))) == NULL)
		exit(-1);
	buff->counter = size;
	if ((buff->str = (char *)ft_memalloc(sizeof(char) * buff->counter)) == NULL)
		exit(-1);
	buff->i = 0;
	return (buff);
}

t_buff					*buff_reload(t_buff *buff, int size)
{
	buff->counter += size;
	if ((buff->str = ft_realloc(buff->str, buff->counter)) == NULL)
		exit(1);
	return (buff);
}

void					buff_del(t_buff **buff)
{
	ft_strdel(&((*buff)->str));
	(*buff)->i = 0;
	(*buff)->counter = 0;
	free(*buff);
	buff = NULL;
}
