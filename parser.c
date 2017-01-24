/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:41:04 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/24 17:01:32 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"

void	calculate_address(t_champ *head)
{
	int		tmp;
	int		i;
	char	*op;

	i = 0;
	tmp = 0;
	while (head)
	{
		if (head->type == OP)
		{
			op = head->line;
			tmp = i;
			i += params_types(head->line);
		}
		if (head->type == REG)
			i += 1;
		if (head->type == DIR)
			i += label_sizes(op);
		if (head->type == IND)
			i += 2;
		head->address = head->type == LABELS ? i : tmp;
		head = head->next;
	}
}

int		get_address(t_labels *labels, char *str)
{
	t_labels *tmp;

	tmp = labels;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp->address);
		tmp = tmp->next;
	}
	return (-1);
}

int		converting_labels(t_champ *head, char *str, t_labels *labels, int len)
{
	int		add;

	add = get_address(labels, str);
	if (add == -1)
		error_and_exit(-1, NULL);
	add -= head->address;
	head->len = len;
	return (add);
}

int		params_values(t_champ *head, t_labels *labels, char *op)
{
	int len;

	len = label_sizes(op);
	if (head->type == REG)
		return (ft_atoi(head->line + 1));
	else if (head->type == DIR)
	{
		if (head->line[1] == LABEL_CHAR)
			return (converting_labels(head, head->line + 2, labels, len * 2));
		else
			return (getting_direct_length(head, head->line + 1, len * 2));
	}
	else if (head->type == IND)
	{
		if (head->line[0] == LABEL_CHAR)
			return (converting_labels(head, head->line + 2, labels, 4));
		else
			return (getting_direct_length(head, head->line, IND_SIZE));
	}
	return (-1);
}

void	calculate_value(t_champ *head, t_labels *labels)
{
	char	*last_op;

	while (head)
	{
		head->encoding = 0;
		if (head->type == NAME || head->type == COMMENT)
			(void)last_op;
		else if (head->type == OP)
		{
			last_op = head->line;
			head->value = get_op_code(head->line, 0) + 1;
			if (params_types(last_op) == 2)
				head->encoding = join_binary_encoding(head);
		}
		else if (head->type == LABELS)
			(void)last_op;
		else
		{
			head->value = params_values(head, labels, last_op);
		}
		head = head->next;
	}
}
