/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/19 17:06:20 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/20 19:45:34 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

t_lst	*ft_lstbefore(t_lst *lst, t_lst *elem)
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

void	ft_lstdelin_memdel(t_lst **alst, t_lst *elem)
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

void	ft_lstadd(t_lst **alst, t_lst *new)
{
	if (new == NULL || alst == NULL)
		return ;
	new->next = *alst;
	*alst = new;
}


void	ft_lstadd_before(t_lst **alst, t_lst *old, t_lst *new)
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

void	ft_lstadd_sorted(t_lst **alst, t_lst *elem,\
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

long long int	ft_atol(const char *str)
{
	long long int	result;
	int				sign;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (*str - '0') + result * 10;
		str++;
	}
	return (result * (long long int)sign);
}

int			ft_isint(char *s_int, int *result)
{
	int				i;
	int				r;
	long long int	tmp;

	i = 0;
	if (s_int[0] == 0)
		return (0);
	while (s_int[i])
	{
		if (!ft_isdigit(s_int[i]) &&
				!(s_int[i] == '-' && i == 0 && s_int[1]))
			return (0);
		i++;
	}
	tmp = ft_atol(s_int);
	r = (int)tmp;
	if ((long long int)r != tmp)
		return (0);
	*result = r;
	return (1);
}

t_lst	*ft_lstnew_noalloc(void *data, size_t data_size)
{
	t_lst *result;

	result = (t_lst*)ft_memalloc(sizeof(t_lst));
	if (result == NULL)
		return (NULL);
	result->next = NULL;
	if (data == NULL)
	{
		result->data = NULL;
		result->data_size = 0;
		return (result);
	}
	result->data_size = data_size;
	result->data = data;
	if (result->data == NULL)
	{
		result->data_size = 0;
		return (NULL);
	}
	return (result);
}
