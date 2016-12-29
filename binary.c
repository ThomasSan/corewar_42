/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:41:09 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 16:41:11 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <stdio.h>

int		getting_direct_length(t_champ *head, char *str, int len)
{
	int ret;

	ret = ft_atoi(str);
	head->len = len;
	return (ret);
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

char	*binary_encoding(t_champ *head, const char *reg)
{
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

	bin = binary_encoding(head, "01");
	dec = binary_todec(bin);
	return (dec);
}
