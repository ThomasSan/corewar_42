/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:52:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/05/12 17:52:33 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoinfree(char *s1, char *s2, int mode)
{
	char *tmp;

	tmp = ft_strjoin(s1, s2);
	if (mode == 1)
		free(s1);
	else if (mode == 2)
		free(s2);
	else
	{
		free(s1);
		free(s2);
	}
	return (tmp);
}

int		lecture(char **str, char **line)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strchr(*str, '\n');
	free(*line);
	*line = ft_strsub(*str, 0, tmp - *str);
	tmp2 = ft_strdup(tmp + 1);
	free(*str);
	*str = tmp2;
	return (1);
}

int		re_lecture2(char *buff, char **line, char **str)
{
	char	*tmp;
	char	*stock;

	tmp = ft_strchr(buff, '\n');
	stock = ft_strsub(buff, 0, tmp - buff);
	*line = ft_strjoinfree(*line, stock, 0);
	free(*str);
	*str = ft_strdup(tmp + 1);
	free(buff);
	return (1);
}

int		re_lecture(const int fd, char **line, char **str, int ret)
{
	char	*tmp2;
	char	*buff;
	int		count;

	count = 0;
	if (*str != '\0')
		*line = ft_strjoinfree(*str, *line, 2);
	buff = ft_strnew(BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		count = 1;
		buff[ret] = '\0';
		if ((tmp2 = ft_strchr(buff, '\n')) != NULL)
			return (re_lecture2(buff, line, str));
		*line = ft_strjoinfree(*line, buff, 1);
	}
	if (ft_strlen(*line) > 0 && count == 0 && ret != -1)
	{
		*str = ft_strjoin(*line, "\n");
		return (lecture(str, line));
	}
	free(buff);
	if (ret == -1)
		return (-1);
	return ((count == 0) ? 0 : 1);
}

int		get_next_line(const int fd, char **line)
{
	static	t_list	*str;
	int				ret;
	t_list			*tmp;
	t_list			*new;

	tmp = str;
	ret = 0;
	if (fd < 0 || !line)
		return (-1);
	*line = ft_strnew(1);
	while (tmp != NULL && tmp->next != NULL && tmp->content_size != (size_t)fd)
		tmp = tmp->next;
	if (tmp == NULL || (tmp->content_size != (size_t)fd && tmp->next == NULL))
	{
		new = (t_list*)malloc(sizeof(t_list));
		new->content_size = (size_t)fd;
		new->content = ft_strnew(1);
		ft_lstadd(&(str), new);
		tmp = str;
	}
	if ((ft_strchr(tmp->content, '\n')) != NULL)
		return (lecture((char**)(&(tmp->content)), line));
	return (re_lecture(fd, line, (char**)(&(tmp->content)), ret));
}
