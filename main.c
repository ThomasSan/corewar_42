/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:52:18 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/05 15:01:57 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>

char	*trim_quotes(char *str)
{
	char	*tmp;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	count = str[0] == '"' ? 1 : 0;
	if (str[ft_strlen(str) - 1] == '"')
		count++;
	if (!(tmp = (char*)malloc(sizeof(char) * (ft_strlen(str) - count + 1))))
		return (NULL);
	if (ft_strlen(str) == 2 && count == 2)
		return (NULL);
	while (str[i])
	{
		while ((i == 0 || i == (int)ft_strlen(str) - 1) && str[i] == '"')
			i++;
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

t_champ	*get_doc(t_champ *head, char *str, int type)
{
	t_champ *new;
	t_champ *tmp;
	char	*tmp1;

	if (!(new = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	tmp1 = str;
	str = ft_strtrim(str);
	new->line = get_dat_line(type, str);
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
			if (get_op_code(ft_strsub(line, start, i - start), 1) > -1)
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
			if (ft_strstr(l, ".name") == l)
				h = get_doc(h, ft_strsub(l, 6, ft_strlen(l) - 6), NAME);
			if (ft_strstr(l, ".comment") == l)
				h = get_doc(h, ft_strsub(l, 9, ft_strlen(l) - 9), COMMENT);
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
	display_document(head);
	calculate_address(head);
	labels = parsing_champ(head);
	calculate_value(head, labels);
	validity_checking(head);
	prog = get_program(head, av[1]);
	write_program(prog, head);
	free_prog(prog, head, labels);
	// while (1);
	return (0);
}
