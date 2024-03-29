/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:41 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 15:58:10 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exit.h"
#include "../../include/parser.h"

int	parser_exit(int error_num, char **str)
{
	if (*str)
		free(*str);
	return (free_and_exit(error_num));
}

int	exit_with_errno(void)
{
	ft_putendl_fd(strerror(errno), 1);
	exit(errno);
}

int	exit_custom_err(int error_num)
{
	if (error_num == ERR_DEBUG)
		write(1, "Error\nSomething went wrong\n", 27);
	exit(error_num);
}

int	free_and_exit(int error_num)
{
	free_data();
	if (error_num == ERRNO)
		return (exit_with_errno());
	else
		return (exit_custom_err(error_num));
}
