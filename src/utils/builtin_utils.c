/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:40 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:40 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libstruct.h"
#include "../../include/libincludes.h"

void		b_put_error(char *name, char *arg, char *message, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (arg)
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	g_data->code = code;
}

int			is_env(char *arg)
{
	int		ind;

	ind = -1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (-1);
	while (arg[++ind] && arg[ind] != '=')
		if (!ft_isalnum(arg[ind]) && arg[ind] != '_')
			return (-1);
	if (arg[ind] == '=')
		return (1);
	return (0);
}
