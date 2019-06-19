/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 19:49:21 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/19 18:20:57 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"

void					ft_mapdelone(t_map *map, const char *key)
{
	int					hash;
	int					(*hash_func)(const char *, int);
	ht_list				**tmp;

	hash_func = map->hashfunc;
	hash = hash_func(key, map->size);
	tmp = &(map->head[hash]);
	if (*tmp == NULL)
		return ;
	while (*tmp != NULL)
	{
		if (ft_strcmp((const char *)(*tmp)->key, key) == 0)
		{
			ht_listdelone(&(map->head[hash]), tmp);
			return ;
		}
		if ((*tmp)->next == NULL)
			return ;
		tmp = &((*tmp)->next);
	}
}
