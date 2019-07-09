/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffreload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qypec <qypec@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 13:44:41 by qypec             #+#    #+#             */
/*   Updated: 2019/07/09 13:50:28 by qypec            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_buffer.h"

void					ft_buffreload(t_buff *buff)
{
	if (buff->i == buff->totalsize - 1)
	{
		buff->totalsize += buff->additional_size;
		if ((buff->str = ft_realloc(buff->str, buff->totalsize)) == NULL)
			exit(1);
	}
}