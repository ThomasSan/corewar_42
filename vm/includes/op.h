/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 21:01:28 by ybeaure           #+#    #+#             */
/*   Updated: 2016/12/15 12:31:01 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# include <stdbool.h>

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4 * 1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHARS		"#;"
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		50
# define NBR_LIVE			21
# define MAX_CHECKS			10

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define REG_NUMBER			16

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct			s_op
{
	char				*name;
	unsigned char		nbr_param;
	char				p_types[4];
	char				opcode;
	int					nbr_cycles;
	char				*comment;
	bool				is_p;
	bool				is_idx;
}						t_op;

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_pro
{
	int					pc;
	int					curr_op;
	int					champ;
	int					cycles_to_exec;
	int					reg[REG_NUMBER];
	int					carry;
	struct s_pro		*next;
	struct s_pro		**start;
	int					lives;
}						t_pro;

typedef struct			s_cycle
{
	t_pro				**pro;
	int					pro_nbr;
	int					cycle_to_die;
	int					cycles_done;
	int					dump_cycle;
	int					checks_done;
}						t_cycle;

#endif
