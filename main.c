#include "assembleur.h"
#include "op.h"
#include <unistd.h>
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
		if (head->type == OP || head->type == REG || 
			head->type == DIR || head->type == IND)
			printf("-> # %d / %d\n", head->value, head->value);
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
				head = get_document(head, ft_strsub(line, 0, i), LABELS);
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

int		get_program_size(t_champ *head)
{
	int		size;
	char	*op;
	t_champ	*tmp;

	size = 0;
	tmp = head;
	op = NULL;
	while (tmp)
	{
		if (tmp->type == OP)
		{
			size += params_types(tmp->line) == 1 ? 2 : 4;
			op = tmp->line;
		}
		if (tmp->type == REG)
			size += 2;
		if (tmp->type == DIR)
			size += label_sizes(op) * 2;
		if (tmp->type == IND)
			size += 2;
		tmp = tmp->next;
	}
	return (size/2);
}

int		write_in_file(char *str, int fd, int i)
{
	int j;

	j = 0;
	while (str[j])
	{
		write(fd, &str[j], 1);
		j++;
		if ((i + j) % (4*8) == 0)
			write(fd, "\n", 1);
		if ((i + j) % 4 == 0 && (i + j) % (4*8) != 0)
			write(fd, " ", 1);
	}
	return (i+j);
}

void	write_magic(int fd)
{
	int		magic;

	magic = COREWAR_EXEC_MAGIC;
	magic = ((magic >> 24) & 0xff) | ((magic << 8) & 0xff0000) |
	((magic >> 8) & 0xff00) | ((magic << 24) & 0xff000000);
	printf("here\n");
	write(fd, (char*)&magic, 4);
}

void	write_file_len(int file_len, int fd)
{
	file_len = ((file_len >> 24) & 0xff) | ((file_len << 8) & 0xff0000) |
	((file_len >> 8) & 0xff00) | ((file_len << 24) & 0xff000000);
	write(fd, (char*)&file_len, 4);
}

void	write_name(char *name, int fd, int len)
{
	write(fd, name, len + 4);
}

int		get_size(int type, char *op)
{
	if (type == REG)
		return (1);
	if (type == IND)
		return (2);
	if (type == DIR)
		return(label_sizes(op));
	return (0);
}

int		fill_tmp(t_champ *head, char *tmp, char *op, int len)
{
	int		size;

	size = get_size(head->type, op);
	// if size == 0 return error;
	if (size == 1)
		tmp[len] = ((size_t)head->value) % 256;
	if (size == 2)
	{
		tmp[len] = ((size_t)head->value) / 256;
		tmp[len + 1] = ((size_t)head->value) % 256;
	}
	if (size == 4)
	{
		tmp[len] = ((size_t)head->value) / (256 * 256 * 256);
		tmp[len + 1] = (((size_t)head->value) - tmp[len] * 256 * 256 * 256)
			/ (256 * 256);
		tmp[len + 2] = (((size_t)head->value) - tmp[len + 1] * 256 * 256) / 256;
		tmp[len + 3] = (((size_t)head->value) - tmp[len + 2] * 256) % 256;
	}
	return (len + size);
}

void	write_commands(t_champ *head, int fd, int len)
{
	char	tmp[14];
	char	*op;

	while (head)
	{
		if (head->type == OP)
		{
			if (len)
				write(fd, tmp, len);
			len = 0;
			tmp[len] = head->value;
			len++;
			printf("%s, %d", head->line, head->value);
			if (head->encoding)
			{
				printf(" || %d\n", head->encoding);
				tmp[len] = head->encoding;
				len++;
			}
			printf("\n");
			op = head->line;
		}
		else if (head->type == REG || 
		head->type == DIR || head->type == IND)
		{
			printf("%s %d\n", head->line, head->value);
			len = fill_tmp(head, tmp, op, len);
		}
		head = head->next;
	}
	write(fd, tmp, len);
}

void	write_program(t_prog *prog, t_champ *head)
{
	int		fd;

	if ((fd = open(prog->file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		printf("ERROR\n");
		return ; // remplacer par function ERROR;
	}
	(void)head;
	write_magic(fd);
	write_name(prog->name, fd, PROG_NAME_LENGTH);
	write_file_len(prog->size, fd);
	write_name(prog->comment, fd, COMMENT_LENGTH);
	write_commands(head, fd, 0);
}

char	*get_file(char *str)
{
	char *tmp;
	char *dst;

	tmp = ft_strsub(str, 0, ft_strlen(str) - 2);
	dst = ft_strjoin("./", tmp);
	free(tmp);
	tmp = dst;
	dst = ft_strjoin(dst, ".cor");
	free(tmp);
	return (dst);
}

char	*get_magic(void)
{
	char	*magic;
	char	*tmp;

	magic = str_itobase(COREWAR_EXEC_MAGIC, 16);
	tmp = magic;
	magic = ft_strjoin("00", magic);
	free(tmp);
	return (magic);
}

char	*get_name(t_champ *head, int type)
{
	int		i;
	int		len;
	char 	*name;
	char	*tmp;

	i = 0;
	while (head)
	{
		if (head->type == type)
			tmp = head->line;
		head = head->next;
	}
	len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	if (!(name = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		name[i] = i < (int)ft_strlen(tmp) ? tmp[i] : 0;
		i++;
	}
	return (name);
}

char	*get_full_prog(t_champ *head)
{
	char	*dst;
	char	*tmp;

	dst = NULL;
	while (head)
	{
		if (head->type == OP || head->type == REG || 
			head->type == DIR || head->type == IND)
		{
			if (dst)
			{
				tmp = dst;
				dst = ft_strjoin(dst, head->hex_value);
				free(tmp);
			}
			else
				dst = ft_strdup(head->hex_value);
		}
		head = head->next;
	}
	return (dst);
}

t_prog	*get_program(t_champ *head, char *name)
{
	t_prog *new;

	(void)name;
	if (!(new = (t_prog*)malloc(sizeof(t_prog))))
		return (NULL);
	(void)head;
	new->file = get_file(name);
	new->name = get_name(head, NAME);
	new->comment = get_name(head, COMMENT);
	new->size = get_program_size(head);
	// new->program = get_full_prog(head);
	return (new);
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
	// display_labels(labels);
	prog = get_program(head, av[1]);
	write_program(prog, head);
	return (0);
}