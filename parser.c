#include "assembleur.h"
#include "op.h"
#include <stdio.h>

int			index_of(char *str, char c)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			label_index(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (index_of(LABEL_CHARS, line[i]) > -1)
			i++;
		else if (line[i] == LABEL_CHAR)
			return (i);
		else
			return (-1);
	}
	return (-1);
}

void		calculate_address(t_champ *head)
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