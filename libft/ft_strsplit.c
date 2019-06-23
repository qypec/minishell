/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:13:16 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 16:16:28 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
# include <stdio.h>

static char				**fill(char **matr, const char *str, char c)
{
	int					i;
	int					size;
	int					tmp_i;
	int					counter;

	i = -1;
	counter = 0;
	while (str[++i] != '\0')
	{
		size = 0;
		tmp_i = i;
		while (str[tmp_i] != c && str[tmp_i] != '\0')
		{
			size++;
			tmp_i++;
		}
		if ((matr[counter] = (char *)ft_memalloc(sizeof(char) * (size + 1))) == NULL)
			return (NULL);
		tmp_i = 0;
		while (str[i] != c && str[i] != '\0')
			matr[counter][tmp_i++] = str[i++];
		matr[counter++][tmp_i] = '\0';
	}
	return (matr);
}

static size_t			get_height(const char *str, char c)
{
	size_t				height;

	height = 0;
	while (*str != '\0')
	{
		if (*str == c)
			height++;
		str++;
	}
	return (height + 1);
}

char				**ft_strsplit(char const *str, char c)
{
	char			**matr;
	int				len;
	int				i;

	if (str == NULL)
		return (NULL);
	len = get_height(str, c) + 1;
	matr = (char **)malloc(sizeof(char *) * len);
	i = 0;
	while (i < len)
		matr[i++] = NULL;
	if ((matr = fill(matr, str, c)) == NULL)
	{
		ft_matrixfree(&matr);
		exit(-1);
	}
	return (matr);
}
