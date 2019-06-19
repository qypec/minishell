/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismapitem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:45:31 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/19 18:15:19 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"

int						ft_ishtabitem(t_map *map, const char *key)
{
	int					hash;
	int					(*hash_func)(const char *, int);
	ht_list				**tmp;

	hash_func = g_hashfunc;
	hash = hash_func(key, map->size);
	tmp = &(map->head[hash]);
	if (*tmp == NULL)
		return (0);
	while (*tmp != NULL)
	{
		if (ft_strcmp((const char *)(*tmp)->key, key) == 0)
			return (hash);
		if ((*tmp)->next == NULL)
			break ;
		tmp = &((*tmp)->next);
	}
	return (0);
}
