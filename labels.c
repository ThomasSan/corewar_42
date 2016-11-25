#include "assembleur.h"
#include "op.h"
#include <stdio.h>

t_labels	*get_labels(t_labels *head, char *line)
{

}

int			index_of(char *str, char c)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int			is_a_label(char *line)
{
	int			i;

	i = 0;
	while (line[i])
	{
		if (index_of(LABEL_CHARS, line[i]))
			i++;
		else if (line[i] == LABEL_CHAR)
			return (1);
	}
	return (0);
}

void		display_labels(t_labels *head)
{
	while (head)
	{
		printf("label : %s -> %d\n", head->name, head->address);
		head = head->next;
	}
}

int			get_address(char *str)
{
	
	return (0);
}

void		parsing_champ(t_champ *head)
{
	t_labels 	*labels;
	int			address;

	labels = NULL;
	address = 0;
	while (head)
	{
		if (is_a_label(head->line))
			labels = get_labels(labels, head->line, address);
		head->address = address;
		address += get_address(head->line);
		head = head->next;
	}
}