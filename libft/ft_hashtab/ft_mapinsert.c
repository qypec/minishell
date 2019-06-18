/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 08:04:48 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 21:30:04 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"
# include <stdio.h>

void					ft_mapinsert(t_map *map, const char *key, const void *value)
{
	int					hash;
	int					(*hash_func)(const char *, int);
	ht_list				**tmp;

	hash_func = map->hashfunc;
	hash = hash_func(key, map->size);
	tmp = &(map->head[hash]);
	if (*tmp == NULL)
	{
		*tmp = ht_listnew(key, value);
		map->content_size++;
		return ;
	}
	while (*tmp != NULL)
	{
		if (ft_strcmp((const char *)(*tmp)->key, key) == 0)
		{
			(*tmp)->value = (void *)value;
			return ;
		}
		if ((*tmp)->next == NULL)
			break ;
		*tmp = (*tmp)->next;
	}
	(*tmp)->next = ht_listnew(key, value);
	map->content_size++;
}
