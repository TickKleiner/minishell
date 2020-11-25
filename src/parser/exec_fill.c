/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:40 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/26 01:30:23 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_exec	*exec_init(void)
{
	t_exec *exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->name = NULL;
	exec->path = NULL;
	exec->argv = NULL;
	exec->env = g_data->l_env;
	exec->pipe_to = NULL;
	exec->pipe_from = NULL;
	exec->fd_new[0] = -2;
	exec->fd_new[1] = -2;
	exec->ret = 0;
	return (exec);
}

static int		cmd_len(t_dlist *lptr, t_exec *exec)
{
	int len;
	int cmd;

	len = (exec->pipe_from) ? 1 : 0;
	while (lptr)
	{
		if ((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
				return (len);
		}
		else if (cmd > 0)
			++len;
		lptr = lptr->next;
	}
	return (len);
}

t_dlist	*process_pipe(t_dlist *newlst, t_exec *exec)
{
	t_exec *newexec;

	free_tokens(&(g_data->lst));
	g_data->lst = newlst;
	//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	newexec = exec_init();
	if (!newexec)
		parser_exit(ERRNO, NULL);
	exec->pipe_to = newexec;
	newexec->pipe_from = exec;
	return (exec_fill(newexec));
}

t_dlist	*end_cmd(t_dlist *lptr, t_exec *exec, int cmd)
{
	t_dlist	*newlst;

	newlst = lptr->next;
	lptr->next = NULL;
	if (cmd == C_END)
		return (newlst);
	return (process_pipe(newlst, exec));
}

static t_dlist	*exec_arr_fill(t_dlist *lptr, t_exec *exec, char **argv)
{
	int		cmd;
	int		i;

	//if (argv[0])
		//printf("argv[0]=%s\n", argv[0]);//
	//printf("argv[0]=%s,%i\n", exec->argv[0], 0);
	i = 0;
	while (lptr)
	{
		if ((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
				return (end_cmd(lptr, exec, cmd));
			else
				process_rdr(exec, &lptr, argv); //else if(!(process_rdr))
//				return (NULL);
			continue ;
		}
		else if ((cmd = ((t_token *)lptr->content)->len) > 0)
		{
			if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
				parser_exit(ERRNO, NULL);
			printf("%s, %i\n", argv[i], i);//
		}
		lptr = lptr->next;
	}
	//argv[++i] = NULL;
	//printf("argv[++i]=%s,%i\n", exec->argv[i+1], i);
	return (NULL);
}

t_dlist	*exec_fill(t_exec *exec)
{
	t_dlist *lptr;
	int		len;

//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	len = cmd_len(g_data->lst, exec);
	//printf("len=%i\n", len);
	if (!(exec->argv = (char **)ft_calloc(sizeof(char *), len + 1)))
	//if (!(exec->argv = (char **)malloc(sizeof(char) * (len + 1))))
		parser_exit(ERRNO, NULL);
	lptr = g_data->lst;
	find_name(&lptr, exec, &(exec->argv[0]));
	//printf("argv[0]=%s\n", exec->argv[0]);
	return (exec_arr_fill(lptr, exec, exec->argv));
}
