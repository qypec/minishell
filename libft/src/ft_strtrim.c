/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 12:33:27 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 17:11:30 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					*ft_strtrim(char const *s)
{
	t_buff				*new_str;
	char				*returned_str;
	int					i;

	new_str = ft_buffinit(50);
	i = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) && s[i] != '\0')
			i++;
		while (s[i] != '\0')
		{
			if (ft_isspace(s[i]))
			{
				if (s[i + 1] != '\0' && !ft_isspace(s[i + 1]))
					ft_buffaddsymb(new_str, ' ');
				i++;
				continue ;
			}
			ft_buffaddsymb(new_str, s[i]);
			i++;
		}
	}
	if (ft_isempty(new_str->str))
		returned_str = NULL;
	else
		returned_str = ft_strdup(new_str->str);
	ft_buffdel(&new_str);
	return (returned_str);
}
