/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchameyr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/05 13:25:32 by cchameyr          #+#    #+#             */
/*   Updated: 2016/09/05 13:25:33 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		select_flags(t_specify *spec, char type)
{
	if (type == '#')
		spec->sharp = True;
	else if (type == '+')
		spec->positive_sign = True;
	else if (type == '-')
		spec->negative_sign = True;
	else if (type == ' ')
		spec->space = True;
	else
		return (_ERROR_);
	return (_SUCCESS_);
}
