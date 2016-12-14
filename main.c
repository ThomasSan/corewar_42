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
			size += label_sizes(op);
		if (tmp->type == OP || tmp->type == REG || 
			tmp->type == DIR || tmp->type == IND)
		{
			size += ft_strlen(tmp->hex_value);

		}
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
	write(fd, (char*)&magic, 4);
}

void	write_file_len(int file_len, int fd)
{
	file_len = ((file_len >> 24) & 0xff) | ((file_len << 8) & 0xff0000) |
	((file_len >> 8) & 0xff00) | ((file_len << 24) & 0xff000000);
	write(fd, (char*)&file_len	, 4);
}

void	write_program(t_prog *prog, t_champ *head)
{
	int		fd;

	if ((fd = open(prog->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) == -1)
	{
		printf("ERROR\n");
		return ; // remplacer par function ERROR;
	}
	char *name;
	char *comment;

	write_magic(fd);
	name = (char*)malloc(sizeof(char) * PROG_NAME_LENGTH + 1);
	ft_bzero(name, PROG_NAME_LENGTH);
	name[0] = 'z';
	name[1] = 'o';
	name[2] = 'r';
	name[3] = 'k';
	write(fd, name, PROG_NAME_LENGTH + 4);
	comment = (char*)malloc(sizeof(char) * COMMENT_LENGTH + 1);
	ft_bzero(comment, COMMENT_LENGTH);
	comment[0] = 'I';
	comment[1] = '\'';
	comment[2] = 'M';
	comment[3] = ' ';
	comment[4] = 'A';
	comment[5] = 'L';
	comment[6] = 'I';
	comment[7] = 'I';
	comment[8] = 'I';
	comment[9] = 'I';
	comment[10] = 'V';
	comment[11] = 'E';
	write_file_len(prog->size, fd);
	write(fd, comment, COMMENT_LENGTH + 4);
	char tmp[14];
	ft_bzero(tmp, 14);
	tmp[0] = 11;
	tmp[1] = 104;
	tmp[2] = 1 % 256;
	tmp[3] = 15 / 256;
	tmp[4] = 15 % 256;
	tmp[5] = 1 / 256;
	tmp[6] = 1 % 256;
	// tmp[6];
	// tmp[7];
	// tmp[8];
	// tmp[9];
	// tmp[10];
	// tmp[11];
	// tmp[12];
	// tmp[13];
	write(fd, tmp, 7);
	(void)head;
	tmp[0] = 6;
	tmp[1] = 100;
	tmp[2] = 1 % 256;
	tmp[3] = 0 / (256 * 256 * 256);
	tmp[4] = (0 - tmp[2] * 256 * 256 * 256) / (256 * 256);
	tmp[5] = (0 - tmp[3] * 256 * 256) / 256;
	tmp[6] = (0 - tmp[4] * 256) / 256;
	tmp[7] = 1 % 256;
	// tmp[6];
	// tmp[7];
	// tmp[8];
	// tmp[9];
	// tmp[10];
	// tmp[11];
	// tmp[12];
	// tmp[13];
	write(fd, tmp, 8);
	(void)head;
	int var = 1;
	tmp[0] = 1;
	tmp[1] = ((size_t)var) / (256 * 256 * 256);
	tmp[2] = (((size_t)var) - tmp[1] * 256 * 256 * 256) / (256 * 256);
	tmp[3] = (((size_t)var) - tmp[2] * 256 * 256) / 256;
	tmp[4] = (((size_t)var) - tmp[3] * 256) / 256;
	// tmp[6];
	// tmp[7];
	// tmp[8];
	// tmp[9];
	// tmp[10];
	// tmp[11];
	// tmp[12];
	// tmp[13];
	write(fd, tmp, 5);
	int val = -5;
	tmp[0] = 9;
	tmp[1] = ((size_t)val) / 256;
	tmp[2] = ((size_t)val) % 256;
	// tmp[6];
	// tmp[7];
	// tmp[8];
	// tmp[9];
	// tmp[10];
	// tmp[11];
	// tmp[12];
	// tmp[13];
	write(fd, tmp, 3);
	(void)head;
	// while (head)
	// {
	// 	if (head->type == OP || head->type == REG || 
	// 		head->type == DIR || head->type == IND)
	// 		{

	// 			printf("head->value %d ", head->value);
	// 			head->value = ((head->value >> 24) & 0xff) | ((head->value << 8) & 0xff0000) |
	// 	((head->value >> 8) & 0xff00) | ((head->value << 24) & 0xff000000);
	// 			printf("head->value %d len %d\n", head->value, head->len);
	// 			write(fd, (char*)&file_len	, 8);
	// 		}
	// 	head = head->next;
	// }
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
	char	*dst;
	char	*tmp;

	len = type == NAME ? PROG_NAME_LENGTH * 2 : COMMENT_LENGTH * 2;
	i = 0;
	len += 8;
	if (!(tmp = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (head)
	{
		if (head->type == type)
			dst = head->hex_value;
		head = head->next;
	}
	while (i < len)
	{
		tmp[i] = i < (int)ft_strlen(dst) ? dst[i] : '0';
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
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
	// new->name = get_name(head, NAME);
	// new->comment = get_name(head, COMMENT);
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