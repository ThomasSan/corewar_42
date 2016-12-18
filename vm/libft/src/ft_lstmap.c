/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 07:11:25 by ybeaure           #+#    #+#             */
/*   Updated: 2015/11/30 09:03:41 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;

	new_list = NULL;
	if (lst && f)
	{
		new_list = (*f)(lst);
		if (lst->next)
			new_list->next = ft_lstmap((lst->next), f);
	}
	return (new_list);
}
