#include "assembleur.h"
#include <stdio.h>

t_champ	*get_document(t_champ *head, char *str)
{
	t_champ *new;
	t_champ *tmp;

	if (!(new = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	new->line = ft_strdup(str);
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

void	display_document(t_champ *head)
{
	while (head)
	{
		printf("head %s\n", head->line);
		head = head->next;
	}
}

int		main(int ac, char **av)
{
	t_champ *head;
	char	*line;
	int		fd;

	head = NULL;
	line = NULL;
	if (ac != 2)
	{
		ft_putendl_fd("Usage ./assembleur [FILE]");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		head = get_document(head, line);
		free(line);
	}
	display_document(head);
	return (0);
}