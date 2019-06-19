/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 17:18:00 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/19 17:49:13 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"

void					ft_mapdel(t_map **map)
{
	int					i;

	i = 0;
	while (i < (*map)->size)
		ht_listdel(&((*map)->head[i++]));
	free((*map)->head);
	free(*map);
	map = NULL;
}
