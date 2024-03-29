/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:52:49 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 21:56:31 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/error.h"
#include <fcntl.h>

static int	process_rdr_left(t_exec *exec, char *filename)
{
	if (exec->fd_new[0] > 1)
		close(exec->fd_new[0]);
	exec->fd_new[0] = open(filename, O_RDONLY);
	if (exec->fd_new[0] < 0)
	{
		error_msg_auto(&exec->ret, filename, 1);
		return (0);
	}
	return (1);
}

static int	process_rdr_right(t_exec *exec, char *filename, int cmd)
{
	if (exec->fd_new[1] > 1)
		close(exec->fd_new[1]);
	if (cmd == C_RDR_R_DBL)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_APPEND, S_IRWXU | S_IROTH);
	if (cmd == C_RDR_R)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_TRUNC, S_IRWXU | S_IROTH);
	if (exec->fd_new[1] < 0)
	{
		error_msg_auto(&exec->ret, filename, 1);
		return (0);
	}
	return (1);
}

int			process_rdr(t_exec *exec, t_dlist **lptr, char **arr)
{
	char	*filename;
	int		cmd;

	cmd = ((t_token *)((*lptr)->content))->len;
	*lptr = (*lptr)->next;
	filename = ((t_token *)((*lptr)->content))->str;
	if (!((t_token *)((*lptr)->content))->len)
	{
		exec->fd_new[1] = -1;
		error_msg_custom(&exec->ret, filename, "ambiguous redirect", 1);
		return (0);
	}
	if (cmd == C_RDR_L)
	{
		if (!process_rdr_left(exec, filename))
			return (0);
	}
	else if (!process_rdr_right(exec, filename, cmd))
		return (0);
	*lptr = (*lptr)->next;
	if (!exec->name)
		find_name(lptr, exec, &arr[0]);
	return (1);
}
