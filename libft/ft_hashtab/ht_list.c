/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:30:10 by yquaro            #+#    #+#             */
/*   Updated: 2019/06/23 13:12:30 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_map.h"

static void				del(ht_list **list)
{
	(*list)->next = NULL;
	(*list)->key = NULL;
	(*list)->value = NULL;
	free(*list);
	list = NULL;
}

void					ht_listdelone(ht_list **head, ht_list **list)
{
	ht_list				*tmp;
	ht_list				*lst;

	if (*list == NULL)
		return ;
	tmp = *head;
	lst = *list;
	if (tmp == lst)
	{
		del(list);
		*list = tmp->next;
		return ;
	}
	if (tmp->next != NULL)
	{
		while (tmp->next != lst)
			tmp = tmp->next;
		tmp->next = lst->next;
	}
	del(&lst);
}

void					ht_listdel(ht_list **head)
{
	ht_list				*tmp;

	if (*head == NULL)
		return ;
	tmp = *head;
	if (tmp->next == NULL)
	{
		ht_listdelone(head, &tmp);
		return ;
	}
	tmp = tmp->next;
	while (tmp != NULL)
	{
		ht_listdelone(head, &tmp);
		tmp = (*head)->next;
	}
	(*head)->next = NULL;
	(*head)->key = NULL;
	(*head)->value = NULL;
	free(*head);
	head = NULL;
}

ht_list					*ht_listnew(const char *key, const void *value)
{
	ht_list				*list;

	if ((list = (ht_list *)malloc(sizeof(ht_list))) == NULL)
		return (NULL);
	list->key = (char *)ft_strdup(key);
	list->value = (void *)value;
	list->next = NULL;
	return (list);
}
