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

char	*get_program_size(t_champ *head)
{
	char	*dst;
	char	*hex;
	char	*tmp;
	int		size;
	int		i;

	size = 0;
	i = -1;
	if (!(dst = (char*)malloc(sizeof(char) * 9)))
		return (NULL);
	while (head)
	{
		if (head->type == OP || head->type == REG || 
			head->type == DIR || head->type == IND)
			size += ft_strlen(head->hex_value);
		head = head->next;
	}
	hex = str_itobase(size/2, 16);
	while (i++ < 8 - (int)ft_strlen(hex))
		dst[i] = '0';
	tmp = dst;
	dst = ft_strjoin(dst, hex);
	free(hex);
	free(tmp);
	return (dst);
}

int		write_in_file(char *str, int fd, int i)
{
	int j;

	j = 0;
	while (str[j])
	{
		write(fd, &str[j], 1);
		j++;
		if ((i + j) % 40 == 0)
			write(fd, "\n", 1);
		if ((i + j) % 4 == 0 && (i + j) % 40 != 0)
			write(fd, " ", 1);
	}
	return (i+j);
}

void	write_program(t_prog *prog)
{
	int		i;
	int		fd;

	i = 0;
	if ((fd = open("./bite.cor", O_APPEND | O_CREAT | O_RDWR, S_IRWXU)) == -1)
	{
		printf("ERROR\n");
		return ; // remplacer par function ERROR;
	}
	i = write_in_file(prog->magic, fd, i);
	i = write_in_file(prog->name, fd, i);
	i = write_in_file(prog->size, fd, i);
	i = write_in_file(prog->comment, fd, i);
	i = write_in_file(prog->program, fd, i);
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

	len = type == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH;
	i = 0;
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
	new->file = get_file(name);
	new->magic = get_magic();
	new->name = get_name(head, NAME);
	new->comment = get_name(head, COMMENT);
	new->size = get_program_size(head);
	new->program = get_full_prog(head);
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
	// display_labels(labels);
	display_document(head);
	prog = get_program(head, av[1]);
	(void)prog;
	write_program(prog);
	return (0);
}