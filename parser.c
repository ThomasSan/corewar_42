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

char	*get_string_hex(char *str)
{
	int		i;
	char	*dst;
	char	*tmp;

	i = 0;
	if (!(dst = (char*)malloc(sizeof(char) * ft_strlen(str) * 2 + 1)))
		return (NULL);
	ft_bzero(dst, ft_strlen(str) * 2 + 1);
	while (str[i])
	{
		tmp = str_itobase(str[i], 16);
		dst = ft_strcat(dst, tmp);
		i++;
		free(tmp);
		tmp = NULL;
	}
	return (dst);
}

void	calculate_value(t_champ *head)
{
	while (head)
	{
		if (head->type == NAME || head->type == COMMENT)
			head->hex_value = get_string_hex(head->line);
		else if (head->type == OP)
			head->hex_value = str_itobase(get_op_code(head->line)+1, 16);
		else
			head->hex_value = NULL;
		head = head->next;
	}
}