/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strglue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:43:32 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 18:18:40 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void						ft_strglue(char **puthere, const char *left, \
											const char *right)
{
	int i;
	int	counter;
	char *str;

	str = *puthere;
	if (str == NULL || left == NULL || right == NULL)
		return ;
	i = 0;
	counter = 0;
	while (str[counter] != '\0')
		counter++;
	while (left[i] != '\0')
	{
		str[counter] = left[i];
		i++;
		counter++;
	}
	i = 0;
	while (right[i] != '\0')
	{
		str[counter] = right[i];
		i++;
		counter++;
	}
	str[counter] = '\0';
}
