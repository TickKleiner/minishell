/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:19 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:19 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"

static void	put_export_env(int fd)
{
	int		ind;
	t_env	*var;

	ind = -1;
	while (g_data->env_arr[++ind])
	{
		var = g_data->env_arr[ind];
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var->key, fd);
		if (var->value)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(var->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
	}
}

static void	parse_export(char *arg, int *code_buf)
{
	int		ret;
	char	**env_buf;
	t_env	*c_env;

	if ((ret = is_env(arg)) == -1)
	{
		*code_buf = 1;
		return (b_put_error("export", arg, "not a valid identifier", 1));
	}
	if (g_data->pid)
		return ;
	if (!(env_buf = ft_split(arg, '=')))
		free_and_exit(ERRNO);
	c_env = find_env_b(env_buf[0]);
	if (c_env && ret == 1)
		change_env_value(c_env, NULL, env_buf[1], env_buf);
	else if (!c_env && ret == 1)
		add_env(env_buf[0], env_buf[1], env_buf);
	else if (!c_env && ret == 0)
		add_env(env_buf[0], NULL, env_buf);
	free_arr(env_buf);
}

int			b_export(t_exec *exec)
{
	int		i;
	int		code_buf;

	code_buf = 0;
	if (!exec->argv[1])
		put_export_env(exec->fd_new[1]);
	i = 0;
	while (exec->argv[++i])
		parse_export(exec->argv[i], &code_buf);
	if (exec->argv[1] && !(g_data->pid))
		remake_lenv();
	return (code_buf);
}
