/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:26:30 by ybeaure           #+#    #+#             */
/*   Updated: 2016/11/30 14:58:05 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

extern t_op		op_tab[17];

int		get_new_p_val(t_vm *vm, t_process *pro, char p_code, int p_val)
{
	int		ret;
	int		i;
	// si c'est un registre, ca prends 1 octet, donc reg[p_val - 1] pour recup l'octet d'avant
	if (p_code == REG_CODE && p_val <= REG_NUMBER)
		return (vm->champs[vm->ram[pro->pc].owner].reg[p_val - 1]);
	// Si c'est sur 3 octets (IND_CODE) ou si value == op_code et qu'il prends un index (dont 3 octets)
	else if (p_code == IND_CODE || (p_code == DIR_CODE && op_tab[vm->ram[pro->pc % MEM_SIZE].value].is_idx > 0))
	{
		ret = 0;
		i = 0;
		while (i != 3)
		{
			// on deplace ret pour faire de la place pour les suivants;
			ret = ret << 8;
			// on add la val de ret avec la valeur de l'octet suivant, et on se deplace avec i (donc 3 octet ez);
			ret = ret + vm->ram[(pro->pc + ((signed short)p_val % IDX_MOD) + i + MEM_SIZE) % MEM_SIZE].value;
			i++;
		}
		// on renvoie les 3 octet a bosser
		return (ret);
	}
	else
		return (p_val);
}

int		check_params(char opcode, char p_code[4], int p_val[4])
{
	int		i;

	i = 0;
	if (opcode > 15)
		return (0);
	while (i < op_tab[(int)opcode - 1].nb_arg)
	{
		// Toujours != 0 -- Si pb dans les types ca return 0
//		if ((op_tab[(int)opcode].p_type[i] >> (p_code[i] - 1)) % 2 == 0)
//		{
//	dprintf(2, "%s\n", op_tab[(int)opcode - 1].comment);
//			return (0);
//		}
		// Check si jamais il a le pcode mais la mauvaise value dans la mem
		dprintf(2, "%#X\n\n", p_code[i]);
		dprintf(2, "%#X\n\n", p_val[i]);
		if (p_code[i] == REG_CODE && p_val[i] > 16)
		{
	dprintf(2, "%s\n", op_tab[(int)opcode - 1].comment);
			return (0);
		}
		i++;
	}
	return (1);
}
