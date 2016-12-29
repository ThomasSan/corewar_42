/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:52:18 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 16:52:19 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>

void	display_document(t_champ *head)
{
	while (head)
	{
		printf("head %s -> %d @ %d", head->line, head->type, head->address);
		if (head->type == OP || head->type == REG ||
			head->type == DIR || head->type == IND)
			printf("-> # %d / %d\n", head->value, head->value);
		else
			printf("\n");
		head = head->next;
	}
}

t_champ	*get_doc(t_champ *head, char *str, int type)
{
	t_champ *new;
	t_champ *tmp;

	if (!(new = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	new->line = ft_strtrim(str);
	new->type = type;
	new->next = NULL;
	if (!head)
		head = new;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	free(str);
	return (head);
}

t_champ	*parse_line(t_champ *head, char *line, int i, int type)
{
	int		start;
	int		ret;

	start = i;
	while (line[i++])
	{
		if (type == OP && ft_isspace(line[i]))
		{
			if (get_op_code(ft_strsub(line, start, i - start)) > -1)
			{
				head = get_doc(head, ft_strsub(line, start, i - start), OP);
				type = 0;
			}
			start = i + 1;
		}
		if (!type && (line[i] == ',' || line[i + 1] == '\0'))
		{
			i = line[i + 1] == '\0' ? i + 1 : i;
			ret = get_param_type(ft_strsub(line, start, i - start));
			if (ret)
				head = get_doc(head, ft_strsub(line, start, i - start), ret);
			start = i + 1;
		}
	}
	return (head);
}

t_champ	*parse_doc(t_champ *h, int fd)
{
	char	*l;
	int		i;

	l = NULL;
	while (get_next_line(fd, &l))
	{
		if (l[0] != '#')
		{
			i = label_index(l);
			if (i > -1)
				h = get_doc(h, ft_strsub(l, 0, i), LABELS);
			if (ft_strstr(l, ".name ") == l)
				h = get_doc(h, ft_strsub(l, 7, ft_strlen(l) - 8), NAME);
			if (ft_strstr(l, ".comment ") == l)
				h = get_doc(h, ft_strsub(l, 10, ft_strlen(l) - 11), COMMENT);
			i = i == -1 ? 0 : i + 1;
		}
		while (l[i] && ft_isspace(l[i]))
			i++;
		h = parse_line(h, l, i, OP);
		free(l);
	}
	return (h);
}

int		main(int ac, char **av)
{
	t_champ		*head;
	t_labels	*labels;
	t_prog		*prog;
	int			fd;

	head = NULL;
	if (ac != 2)
	{
		ft_putendl_fd("Usage ./assembleur [FILE]", 2);
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);
	head = parse_doc(head, fd);
	close(fd);
	calculate_address(head);
	labels = parsing_champ(head);
	calculate_value(head, labels);
	display_document(head);
	validity_checking(head);
	prog = get_program(head, av[1]);
	write_program(prog, head);
	return (0);
}
