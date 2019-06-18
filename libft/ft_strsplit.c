/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:13:16 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 08:09:26 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t			strlen_c(const char *str, char c)
{
	int					i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static size_t			ft_height(const char *str, char c)
{
	size_t				height;

	height = 0;
	while (*str != '\0')
	{
		if (*str == c)
			height++;
		str++;
	}
	return (height);
}

char				**ft_strsplit(char const *str, char c)
{
	char			**matr;
	int				len;
	int				i;

	if (str == NULL)
		return (NULL);
	len = 0;
	i = 0;
	matr = (char **)malloc(sizeof(char *) * (ft_height(str, c) + 1));
	while (str[len] != '\0')
	{
		len = strlen_c(str ,c);
		if ((matr[i] = (char *)malloc(sizeof(char) * len)) == NULL)
		{
			ft_matrixfree(&matr);
			return (NULL);
		}
		ft_strncpy(matr[i++], str, len);
		str = str + len + 1;
		len = 0;
	}
	matr[i] = NULL;
	return (matr);
}
