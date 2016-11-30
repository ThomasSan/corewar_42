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
	str_tmp = str;	
	str = ft_strjoin(str, "00");
	free(str_tmp);
	return (str);
}

char	*join_binary_encoding(t_champ *head, char *str)
{
	char	*bin;
	int		dec;
	char	*hex;
	char	*tmp;

	bin = binary_encoding(head);
	dec = binary_todec(bin);
	hex = str_itobase(dec, 16);
	tmp = str;
	tmp = ft_strjoin(str, hex);
	free(str);
	free(bin);
	free(hex);
	return (tmp);
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

char 	*converting_labels(int address, char *str, t_labels *labels, int len)
{
	char	*tmp;
	char	*tmp1;
	char	*dst;
	int		add;
	int		i;

	i = 0;
	if (!(dst = (char*)malloc(sizeof(char)* len + 1)) || get_address(labels, str) == -1)
		return (NULL);
	add = get_address(labels, str) - address;
	if (add >= 0)
		tmp = str_itobase(add, 16);
	else
		tmp = neg_itobase(add);
	len -= ft_strlen(tmp);
	while (i < len)
	{
		dst[i] = add >= 0 ? '0' : 'f';
		i++;
	}
	tmp1 = dst;
	dst = ft_strjoin(dst, tmp);
	free(tmp1);
	free(tmp);
	return (dst);
}

char 	*getting_direct_length(char *str, int len)
{
	int		i;
	int		nb;
	char	*hex;
	char	*tmp;
	char	*dst;

	i = 0;
	nb = ft_atoi(str);
	hex = str_itobase(nb, 16);
	if (!(dst = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	len -= ft_strlen(hex);
	while (i < len)
	{
		dst[i] = '0';
		i++;
	}
	dst[i] = '\0';
	tmp = dst;
	dst = ft_strjoin(dst, hex);
	free(hex);
	free(tmp);
	return (dst);
}

char	*params_values(t_champ *head, t_labels *labels, char *op)
{
	int	len;

	len = label_sizes(op);
	if (head->type == REG)
		return (str_itobase(ft_atoi(head->line + 1), 16));
	else if (head->type == DIR)
	{
		if (head->line[1] == LABEL_CHAR)
			return (converting_labels(head->address, head->line + 2, labels, len * 2));
		else
			return (getting_direct_length(head->line + 1, len * 2));
	}
	else if (head->type == IND)
	{
		if (head->line[0] == LABEL_CHAR)
			return (converting_labels(head->address, head->line + 2, labels, 4));
		else
			return (getting_direct_length(head->line + 1, IND_SIZE));
	}
	return (NULL);
}

void	calculate_value(t_champ *head, t_labels *labels)
{
	char	*last_op;

	while (head)
	{
		if (head->type == NAME || head->type == COMMENT)
			head->hex_value = get_string_hex(head->line);
		else if (head->type == OP)
		{
			last_op = head->line;
			head->hex_value = str_itobase(get_op_code(head->line)+1, 16);
			if (params_types(last_op) == 2) // a une operation de conversion;
				head->hex_value = join_binary_encoding(head, head->hex_value);
		}
		else if (head->type == LABELS)
			head->hex_value = NULL;
		else
			head->hex_value = params_values(head, labels, last_op);
		head = head->next;
	}
}