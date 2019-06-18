/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ismapitem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:45:31 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/18 19:57:05 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"

int						ft_ishtabitem(ht_list *htab, const char *key)
{
	int					hash;
	int					(*hash_func)(const char *);
	ht_list				*tmp;

	hash_func = g_hashfunc;
	hash = hash_func(key);
	if (&htab[hash] == NULL)
		return (0);
	tmp = &htab[hash];
	while (tmp != NULL)
	{
		if (ft_strcmp((const char *)tmp->key, key) == 0)
			return (hash);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (0);
}
