/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 17:50:58 by ybeaure           #+#    #+#             */
/*   Updated: 2016/05/12 18:09:33 by ybeaure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

int		re_lecture(const int fd, char **line, char **str, int ret);
int		re_lecture2(char *buff, char **line, char **str);
int		lecture(char **str, char **line);
int		get_next_line(const int fd, char **line);
char	*ft_strjoinfree(char *s1, char *s2, int	mode);

# define BUFF_SIZE 200

#endif
