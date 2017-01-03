/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:03:45 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 17:03:59 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>

char	*get_file(char *str)
{
	char *tmp;
	char *dst;

	tmp = ft_strsub(str, 0, ft_strlen(str) - 2);
	dst = ft_strjoin("./", tmp);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, ".cor");
	free(tmp);
	return (dst);
}

char	*get_full_prog(t_champ *head)
{
	char	*dst;
	char	*tmp;

	dst = NULL;
	while (head)
	{
		if (head->type == OP || head->type == REG ||
			head->type == DIR || head->type == IND)
		{
			if (dst)
			{
				tmp = dst;
				dst = ft_strjoin(dst, head->hex_value);
				free(tmp);
			}
			else
				dst = ft_strdup(head->hex_value);
		}
		head = head->next;
	}
	return (dst);
}

char	*get_name(t_champ *head, int type)
{
	int		i;
	int		len;
	char	*name;
	char	*tmp;

	i = 0;
	while (head)
	{
		if (head->type == type)
			tmp = head->line;
		head = head->next;
	}
	len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (!(name = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		name[i] = i < (int)ft_strlen(tmp) ? tmp[i] : 0;
		i++;
	}
	return (name);
}

int		get_program_size(t_champ *head)
{
	int		size;
	char	*op;
	t_champ	*tmp;

	size = 0;
	tmp = head;
	op = NULL;
	while (tmp)
	{
		if (tmp->type == OP)
		{
			size += params_types(tmp->line) == 1 ? 2 : 4;
			op = tmp->line;
		}
		if (tmp->type == REG)
			size += 2;
		if (tmp->type == DIR)
			size += label_sizes(op) * 2;
		if (tmp->type == IND)
			size += 4;
		tmp = tmp->next;
	}
	return (size / 2);
}

t_prog	*get_program(t_champ *head, char *name)
{
	t_prog *new;

	(void)name;
	if (!(new = (t_prog*)malloc(sizeof(t_prog))))
		return (NULL);
	(void)head;
	new->file = get_file(name);
	new->name = get_name(head, NAME);
	new->comment = get_name(head, COMMENT);
	new->size = get_program_size(head);
	return (new);
}
