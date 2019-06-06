/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:55:09 by yquaro            #+#    #+#             */
/*   Updated: 2019/05/01 19:04:31 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_realloc(char *str, size_t size)
{
	char			*new_str;
	size_t			i;

	i = 0;
	if ((new_str = (char *)ft_memalloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	new_str = ft_strcpy(new_str, str);
	ft_strdel(&str);
	return (new_str);
}
