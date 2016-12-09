/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:19:38 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/09 17:53:56 by cchameyr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
  {
  if (check_params(8, p_code, p_val))
  {
  vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1] = get_new_p_val(
  vm, pro, p_code[0], p_val[0]) ^ get_new_p_val(
  vm, pro, p_code[1], p_val[1]);
  if (vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1])
  pro->carry = 1;
  else
  pro->carry = 0;
  }
  }

  void		ft_or(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
  {
  if (check_params(7, p_code, p_val))
  {
  vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1] = get_new_p_val(
  vm, pro, p_code[0], p_val[0]) | get_new_p_val(
  vm, pro, p_code[1], p_val[1]);
  if (vm->champs[vm->ram[pro->pc].owner].reg[p_val[2] - 1])
  pro->carry = 1;
  else
  pro->carry = 0;
  }
  }
  */

void		ft_xor(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	static int	i = 0;
	if (check_params(8, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) ^ get_new_p_val(vm, pro, p_code[1], p_val[1]);



		if (get_new_p_val(vm, pro, p_code[0], p_val[0]) == 14 && i == 0)
		{
			i = 0;
			vm->A_supprimer = pro;
		}



		if (pro->reg[p_val[2] - 1] == 0)
		{
			ft_printf("CARRY = 1\ncycle : %d\n", vm->cycle.cycles);
			pro->carry = 1;
		}
		else
		{
			if (pro == vm->A_supprimer)
			{
				ft_printf("CARRY = 0\ncycle : %d\nvalue REG : %d\n", vm->cycle.cycles, pro->reg[p_val[2] - 1]);
				ft_printf("gnpv 1 : %#x\ngnpv 2 : %#x\n", get_new_p_val(vm, pro, p_code[0], p_val[0]), get_new_p_val(vm, pro, p_code[1], p_val[1]));
				ft_printf("p_val[1] : %#X\n", p_val[1]);
			}
			pro->carry = 0;
		}

	}
}

void		ft_or(t_vm *vm, t_process *pro, char p_code[4], int p_val[4])
{
	if (check_params(7, p_code, p_val))
	{
		pro->reg[p_val[2] - 1] = get_new_p_val(vm, pro, p_code[0], p_val[0]) | get_new_p_val(vm, pro, p_code[1], p_val[1]);
		if (pro->reg[p_val[2] - 1])
			pro->carry = 0;
		else
			pro->carry = 1;
	}
}
