/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_converter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:58:26 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/24 17:01:20 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"

int		argument_number(char *str)
{
	const char	*one_arg[] = {"live", "zjmp", "fork", "lfork", "aff"};
	const char	*two_arg[] = {"ld", "lld", "st"};
	const char	*three_arg[] = {"add", "sub", "and", "or", "xor", "ldi",
	"lldi", "sti"};

	if (index_array(one_arg, str, 5) > -1)
		return (1);
	if (index_array(two_arg, str, 3) > -1)
		return (2);
	if (index_array(three_arg, str, 8) > -1)
		return (3);
	return (-1);
}

int		type_diff(int cat, int type)
{
	if (cat == type)
		return (1);
	if (cat == INDDIR && (type == IND || type == DIR))
		return (1);
	if (cat == INDREG && (type == REG || type == IND))
		return (1);
	if (cat == DIRREG && (type == REG || type == DIR))
		return (1);
	if (cat == ALL && (type == REG || type == IND || type == DIR))
		return (1);
	return (-1);
}

int		check_type1(char *str)
{
	int			cat;
	const char	*reg[] = {"lld", "ld", "add", "sub"};

	cat = -1;
	if (index_array(reg, str, 4) > -1)
		cat = REG;
	else if (ft_strcmp(str, "st") == 0)
		cat = INDREG;
	else if (ft_strcmp(str, "lldi") == 0)
		cat = DIRREG;
	else
		cat = ALL;
	return (cat);
}

int		check_type2(char *str)
{
	int			cat;

	cat = -1;
	if (ft_strcmp(str, "sti") == 0)
		cat = DIRREG;
	else
		cat = REG;
	return (cat);
}

int		check_arg_type(char *str, int type, int i)
{
	int			cat;
	const char	*dir[] = {"live", "zjmp", "fork", "lfork"};
	const char	*reg[] = {"st", "aff", "add", "sub", "sti"};
	const char	*ind_dir[] = {"lld", "ld"};

	if (i == 0)
	{
		cat = -1;
		if (index_array(dir, str, 4) > -1)
			cat = DIR;
		else if (index_array(reg, str, 5) > -1)
			cat = REG;
		else if (index_array(ind_dir, str, 2) > -1)
			cat = INDDIR;
		else
			cat = ALL;
	}
	if (i == 1)
		cat = check_type1(str);
	if (i == 2)
		cat = check_type2(str);
	return (type_diff(cat, type));
}
