/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:36 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/09 02:03:32 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libincludes.h"
#include "../../include/libbuiltins.h"
#include "../../include/error.h"

int			is_builtin(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (1);
	else if (!(ft_strcmp(exec->name, "echo")))
		return (1);
	else if (!(ft_strcmp(exec->name, "env")))
		return (1);
	else if (!(ft_strcmp(exec->name, "exit")))
		return (1);
	else if (!(ft_strcmp(exec->name, "export")))
		return (1);
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (1);
	else if (!(ft_strcmp(exec->name, "unset")))
		return (1);
	else
		return (0);
}

int			ft_processor(t_exec *exec)
{
	if (exec->pipe_to)
		ft_pipe(exec);
	else if (exec->fd_new[0] == 0 && exec->fd_new[1] == 1)
	{
		if (exec->name)
			g_data->code = ft_execute(exec);
	}
	else if (exec->name)
		g_data->code = redir_execute(exec);
	return (0);
}
