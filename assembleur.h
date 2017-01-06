/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembleur.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsanzey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/29 16:32:41 by tsanzey           #+#    #+#             */
/*   Updated: 2016/12/29 16:32:43 by tsanzey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLEUR_H
# define ASSEMBLEUR_H

# define LABELS 100
# define OP 102
# define REG 103
# define DIR 104
# define IND 105
# define NAME 106
# define COMMENT 107
# define ALL 108
# define INDDIR 109
# define INDREG 110
# define DIRREG 111

# include "get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_labels
{
	int				address;
	char			*name;
	struct s_labels	*next;
}					t_labels;

typedef struct		s_champ
{
	char			*line;
	int				address;
	int				type;
	int				value;
	int				encoding;
	int				len;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_prog
{
	char			*file;
	char			*name;
	int				size;
	char			*comment;
}					t_prog;

/*
** Parsing functions
*/
int					label_index(char *line);
int					get_op_code(char *str, int del);
int					get_param_type(char *str);
int					params_types(char *str);
int					label_sizes(char *str);
void				calculate_address(t_champ *head);
void				calculate_value(t_champ *head, t_labels *labels);
int					index_of(char *str, char c);

/*
** Conversion Functions
*/
char				*str_itobase(int nb, int base);
char				*neg_itobase(int nb);
int					binary_todec(char *bin);
int					argument_number(char *str);
int					check_arg_type(char *str, int type, int i);
int					index_array(char const *a[], char *s, int l);
void				validity_checking(t_champ *head);
t_labels			*parsing_champ(t_champ *head);
void				display_labels(t_labels *head);
char				*get_string_hex(char *str);
/*
** Misc
*/
t_prog				*get_program(t_champ *head, char *name);
t_champ				*get_doc(t_champ *head, char *str, int type);
int					getting_direct_length(t_champ *head, char *str, int len);
int					join_binary_encoding(t_champ *head);
void				error_and_exit(int err, char *str);
void				display_document(t_champ *head);
char				*trim_quotes(char *str);
char				*get_dat_line(int type, char *str);
char				*copy_str(char *dst, char *src, int len);
/*
** write functions
*/
void				write_magic(int fd);
void				write_program(t_prog *prog, t_champ *head);
/*
** free
*/
void				free_prog(t_prog *prog, t_champ *head, t_labels *labels);
#endif
