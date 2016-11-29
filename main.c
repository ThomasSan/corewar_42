#include "assembleur.h"
#include "op.h"
#include <stdio.h>

t_champ	*get_document(t_champ *head, char *str, int type)
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

void	display_document(t_champ *head)
{
	while (head)
	{
		printf("head %s -> %d @ %d", head->line, head->type, head->address);
		if (head->hex_value)
			printf("-> # %s\n", head->hex_value);
		else
			printf("\n");
		head = head->next;
	}
}

t_champ		*parse_line(t_champ *head, char *line, int i, int type)
{
	int		start;
	int		ret;

	start = i;
	while (line[i++])
	{
		if (type == OP && ft_isspace(line[i]))
		{
			// printf("op code %d\n", get_op_code(ft_strsub(line, start, i - start)));
			if (get_op_code(ft_strsub(line, start, i - start)) > -1)
			{
				head = get_document(head, ft_strsub(line, start, i - start), OP);
				type = 0;
			}
			start = i + 1;
		}
		if (!type && (line[i] == ',' || line[i + 1] == '\0'))
		{
			i = line[i + 1] == '\0' ? i + 1 : i;
			ret = get_param_type(ft_strsub(line, start, i - start));
			if (ret)
				head = get_document(head, ft_strsub(line, start, i - start), ret);
			start = i + 1;
		}
	}
	return (head);
}

t_champ	*parse_doc(t_champ *head, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] != '#')
		{
			i  = label_index(line);
			if (i > -1)
			{
				// printf("label : %s -> %d\n", ft_strsub(line, 0, label_index(line)), label_index(line));
				head = get_document(head, ft_strsub(line, 0, i), LABELS);
			}
			if (ft_strstr(line, ".name ") == line)
				head = get_document(head, ft_strsub(line, 7, ft_strlen(line) - 8), NAME);
			if (ft_strstr(line, ".comment ") == line)
				head = get_document(head, ft_strsub(line, 10, ft_strlen(line) - 11), COMMENT);
			i = i == -1 ? 0 : i + 1;
		}
		while (line[i] && ft_isspace(line[i]))
			i++;
		head = parse_line(head, line, i, OP);
		free(line);
	}
	return (head);
}

int		main(int ac, char **av)
{
	t_champ *head;
	int		fd;

	head = NULL;
	if (ac != 2)
	{
		ft_putendl_fd("Usage ./assembleur [FILE]", 2);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	head = parse_doc(head, fd);
	calculate_address(head);
	calculate_value(head);
	display_document(head);
	return (0);
}