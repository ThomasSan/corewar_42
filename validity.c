/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:52:26 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 16:52:30 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <stdio.h>

void	error_and_exit(int err, char *str)
{
	if (err == NAME)
		ft_putendl_fd("name error", 2);
	if (err == COMMENT)
		ft_putendl_fd("comment error", 2);
	if (err == 0)
	{
		ft_putstr_fd("arguments number error after ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == 1)
	{
		ft_putstr_fd("wrong type of arguments after ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == -1)
		ft_putendl_fd("Error", 2);
	if (err == OP)
	{
		ft_putstr_fd("Operation is either missing or unknown around ", 2);
		ft_putendl_fd(str, 2);
	}
	if (err == 11)
		ft_putendl_fd("Input file error", 2);
	exit(0);
}

void	name_checking(t_champ *head, int type)
{
	int	count;
	int	len;
	int	max_len;

	count = 0;
	max_len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (!head->line)
		error_and_exit(type, NULL);
	while (head)
	{
		if (head->type == type)
		{
			len = ft_strlen(head->line);
			count++;
		}
		head = head->next;
	}
	if (count != 1)
		error_and_exit(type, NULL);
	if (len > max_len)
		error_and_exit(type, NULL);
}

void	arg_numbers(t_champ *head)
{
	char	*last_op;
	int		nb_op;

	nb_op = 0;
	last_op = NULL;
	while (head)
	{
		if (head->type == OP)
		{
			if (last_op)
				if (nb_op != argument_number(last_op))
					error_and_exit(0, last_op);
			nb_op = 0;
			last_op = head->line;
		}
		if (head->type == IND || head->type == DIR || head->type == REG)
			nb_op++;
		head = head->next;
	}
}

void	arg_types(t_champ *head)
{
	char	*last_op;
	int		nb_op;

	nb_op = 0;
	last_op = NULL;
	while (head)
	{
		if (head->type == OP)
		{
			nb_op = 0;
			last_op = head->line;
		}
		if (head->type == IND || head->type == DIR || head->type == REG)
		{
			if (check_arg_type(last_op, head->type, nb_op) == -1)
				error_and_exit(1, last_op);
			nb_op++;
		}
		head = head->next;
	}
}

void	validity_checking(t_champ *head)
{
	name_checking(head, NAME);
	name_checking(head, COMMENT);
	arg_numbers(head);
	arg_types(head);
}
