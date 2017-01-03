/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 13:03:53 by tsanzey           #+#    #+#             */
/*   Updated: 2017/01/03 13:03:54 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembleur.h"
#include "op.h"
#include <unistd.h>
#include <stdio.h>

void	free_labels(t_labels *labels)
{
	t_labels *tmp;

	while (labels)
	{
		tmp = labels;
		labels = labels->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_champ(t_champ *champ)
{
	t_champ *tmp;

	while (champ)
	{
		tmp = champ;
		champ = champ->next;
		free(tmp->line);
		tmp->line = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_pg(t_prog *prog)
{
	free(prog->file);
	free(prog->name);
	free(prog->comment);
	free(prog);
}

void	free_prog(t_prog *prog, t_champ *champ, t_labels *labels)
{
	(void)prog;
	(void)labels;
	(void)champ;
	free_labels(labels);
	free_champ(champ);
	free_pg(prog);
}