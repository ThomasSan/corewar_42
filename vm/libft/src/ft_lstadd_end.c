/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 04:13:29 by ybeaure           #+#    #+#             */
/*   Updated: 2016/03/27 16:56:35 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **beg_lst, void const *content, size_t cont_size)
{
	t_list	*list;
	t_list	*tmp;

	list = NULL;
	tmp = NULL;
	if (!(list = ft_lstnew(content, cont_size)))
		return ;
	if (!(*beg_lst))
		*beg_lst = list;
	else
	{
		tmp = *beg_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = list;
		list->previous = tmp;
	}
}
