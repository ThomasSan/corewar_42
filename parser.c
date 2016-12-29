#include "assembleur.h"
#include "op.h"
#include <stdio.h>

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
		dst = ft_strjoin(dst, tmp);
		i++;
		free(tmp);
		tmp = NULL;
	}
	return (dst);
}

char	*fill_binary(char *str)
{
	char	*tmp;

	while (ft_strlen(str) < 8)
	{
		tmp = str;
		str = ft_strjoin(str, "0");
		free(tmp);
	}
	return (str);
}

char	*binary_encoding(t_champ *head)
{
	const char	*reg = "01";
	const char	*dir = "10";
	const char	*ind = "11";
	char		*str;
	char		*str_tmp;
	t_champ		*tmp;

	tmp = head->next;
	str = "";
	while (tmp && tmp->type != OP && tmp->type != LABELS)
	{
		str_tmp = str;
		if (tmp->type == REG)
			str = ft_strjoin(str, reg);
		else if (tmp->type == DIR)
			str = ft_strjoin(str, dir);
		else if (tmp->type == IND)
			str = ft_strjoin(str, ind);
		if (ft_strlen(str_tmp) > 0)
			free(str_tmp);
		tmp = tmp->next;
	}
	return (fill_binary(str));
}

int		join_binary_encoding(t_champ *head)
{
	char	*bin;
	int		dec;

	bin = binary_encoding(head);
	dec = binary_todec(bin);
	return (dec);
}

int		get_address(t_labels *labels, char *str)
{
	t_labels *tmp;

	tmp = labels;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, str) == 0)
			return (tmp->address);
		tmp = tmp->next;
	}
	return (-1); // todo create ERROR FN 
	//si on ne trouve pas de matching labels
}

int 	converting_labels(t_champ *head, char *str, t_labels *labels, int len)
{
	int		add;

	add = get_address(labels, str) - head->address;
	head->len = len;
	return (add);
}

int		getting_direct_length(t_champ *head, char *str, int len)
{
	int ret;

	ret = ft_atoi(str);
	head->len = len;
	return (ret);
}

int		params_values(t_champ *head, t_labels *labels, char *op)
{
	int len;

	len = label_sizes(op);
	if (head->type == REG)
		return (ft_atoi(head->line + 1));
	else if (head->type == DIR)
	{
		if (head->line[1] == LABEL_CHAR)
			return (converting_labels(head, head->line + 2, labels, len * 2));
		else
			return (getting_direct_length(head, head->line + 1, len * 2));
	}
	else if (head->type == IND)
	{
		if (head->line[0] == LABEL_CHAR)
			return (converting_labels(head, head->line + 2, labels, 4));
		else
			return (getting_direct_length(head, head->line + 1, IND_SIZE));
	}
	return (-1);
}

void	calculate_value(t_champ *head, t_labels *labels)
{
	char	*last_op;

	while (head)
	{
		head->encoding = 0;
		if (head->type == NAME || head->type == COMMENT)
			head->hex_value = get_string_hex(head->line);
		else if (head->type == OP)
		{
			last_op = head->line;
			head->value = get_op_code(head->line) + 1;
			if (params_types(last_op) == 2) // a une operation de conversion;
				head->encoding = join_binary_encoding(head);
		}
		else if (head->type == LABELS)
			head->hex_value = NULL;
		else
		{
			head->value = params_values(head, labels, last_op);
		}
		head = head->next;
	}
}