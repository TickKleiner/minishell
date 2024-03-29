/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 18:47:12 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:44:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <errno.h>
# include <string.h>
# include "../libft/libft.h"

# define ERRNO -2
# define ERR_DEBUG -1

int		exit_with_errno(void);
int		exit_custom_err(int error_num);
int		free_and_exit(int error_num);

int		parse_line_exit(int error_num, char **line);
int		parser_exit(int error_num, char **str);

#endif
