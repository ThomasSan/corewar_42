/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:06:20 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:43:17 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_lst		*ft_lstbefore(t_lst *lst, t_lst *elem)
{
	if (lst == elem)
		return (NULL);
	while (lst->next != elem && lst->next != NULL)
		lst = lst->next;
	if (lst->next == NULL)
		return (NULL);
	else
		return (lst);
}

void		ft_lstdelin_memdel(t_lst **alst, t_lst *elem)
{
	t_lst *before;

	if ((alst == NULL || *alst == NULL) || elem == NULL)
		return ;
	if (*alst == elem)
		*alst = elem->next;
	else
	{
		before = ft_lstbefore(*alst, elem);
		if (before != NULL)
			before->next = elem->next;
	}
	if (elem->data != NULL)
		ft_memdel(&(elem->data));
	free(elem);
}

void		ft_lstadd(t_lst **alst, t_lst *new)
{
	if (new == NULL || alst == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}

void		ft_lstadd_before(t_lst **alst, t_lst *old, t_lst *new)
{
	t_lst *temp;

	if ((alst == NULL || *alst == NULL) || new == NULL || old == NULL)
		return ;
	if (*alst == old)
	{
		ft_lstadd(alst, new);
		return ;
	}
	temp = ft_lstbefore(*alst, old);
	if (temp == NULL)
		return ;
	new->next = old;
	temp->next = new;
}

void		ft_lstadd_sorted(t_lst **alst, t_lst *elem,\
		int (*cmp)(void *c1, void *c2))
{
	if (alst == NULL || elem == NULL || cmp == NULL)
		return ;
	if (*alst == NULL)
	{
		ft_lstadd(alst, elem);
		return ;
	}
	if (cmp(elem->data, (*alst)->data) <= 0)
		ft_lstadd_before(alst, *alst, elem);
	else if ((*alst)->next == NULL)
		(*alst)->next = elem;
	else
		ft_lstadd_sorted(&((*alst)->next), elem, cmp);
}
