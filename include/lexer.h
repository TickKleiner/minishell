/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:56 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:25:10 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "parserstruct.h"

# define METACHAR "|;<> \t\n"

typedef struct	s_vld
{
	char		*prv;
	const char	*nxt[50];
}				t_vld;

void			correct_tokens(void);
int				split_line(char *line, int mode);
int				get_tokens(char *line, int last_char);
char			*str_mask(char *str, int len);
void			check_syntax_error(t_dlist **last);
void			validate_tokens(int q);

#endif