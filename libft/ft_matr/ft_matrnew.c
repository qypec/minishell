/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 20:30:01 by yquaro            #+#    #+#             */
/*   Updated: 2019/08/13 18:38:53 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char					**ft_matrnew(const char *first_str, ...)
{
	char				**matr;
	va_list				arg;
	int					number_of_elements;
	int					i;

	if (first_str == NULL)
		return (NULL);
	va_start(arg, first_str);
	number_of_elements = 1;
	while (va_arg(arg, char*) != NULL)
		number_of_elements++;
	va_end(arg);
	if ((matr = (char **)malloc(sizeof(char *) * \
							(number_of_elements + 1))) == NULL)
		return (NULL);
	matr[number_of_elements] = NULL;
	va_start(arg, first_str);
	matr[0] = ft_strdup(first_str);
	i = 1;
	while (--number_of_elements)
		matr[i++] = ft_strdup(va_arg(arg, char *));
	va_end(arg);
	return (matr);
}
