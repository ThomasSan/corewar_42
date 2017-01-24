/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 17:03:45 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/24 16:59:45 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>

char	*get_dat_line(int type, char *str)
{
	char	*tmp;

	if (ft_strlen(str) == 0)
		error_and_exit(-1, NULL);
	if (type == NAME || type == COMMENT)
		tmp = trim_quotes(str);
	else
		tmp = ft_strdup(str);
	return (tmp);
}

char	*get_file(char *str)
{
	char	*tmp;
	char	*dst;
	int		len;

	len = ft_strlen(str);
	if (len < 2)
		error_and_exit(11, NULL);
	// if (str[len - 1] != 's' || str[len - 1] != '.')
	// 	error_and_exit(11, NULL);
	tmp = ft_strsub(str, 0, len - 2);
	dst = ft_strjoin("./", tmp);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, ".cor");
	free(tmp);
	return (dst);
}

char	*get_name(t_champ *head, char *name, int type)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (head)
	{
		if (head->type == type)
			tmp = head->line;
		head = head->next;
	}
	len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
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

	if (!(new = (t_prog*)malloc(sizeof(t_prog))))
		return (NULL);
	new->file = get_file(name);
	get_name(head, new->name, NAME);
	get_name(head, new->comment, COMMENT);
	new->size = get_program_size(head);
	return (new);
}
