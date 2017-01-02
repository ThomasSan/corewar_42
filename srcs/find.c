/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 18:16:44 by ybeaure           #+#    #+#             */
/*   Updated: 2017/01/02 16:30:10 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_process	*find_pro_id(t_lst *elem, int id)
{
	t_process	*pro;

	if (elem == NULL)
		return (NULL);
	pro = (t_process*)elem->data;
	if (pro->numero == id)
		return (elem->data);
	else
		return (find_pro_id(elem->next, id));
}
