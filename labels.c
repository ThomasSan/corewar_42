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

t_labels	*get_labels(t_labels *head, int	address, char *name)
{
	t_labels *tmp;
	t_labels *new;

	if (!(new = (t_labels*)malloc(sizeof(t_labels))))
		return (NULL);
	new->next = NULL;
	new->name = ft_strdup(name);
	new->address = address;
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

void		display_labels(t_labels *head)
{
	while (head)
	{
		printf("label : %s -> %d\n", head->name, head->address);
		head = head->next;
	}
}

t_labels 	*parsing_champ(t_champ *head)
{
	t_labels 	*labels;

	labels = NULL;
	while (head)
	{
		if (head->type == LABELS)
			labels = get_labels(labels, head->address, head->line);
		head = head->next;
	}
	return (labels);
}