/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/29 23:22:29 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"
#include "../../include/lexer.h"
#include "../../include/libincludes.h"

void	analise_tokens(void)
{
	t_dlist	*newlst;

	while (g_data->lst)
	{
		if (!(g_data->exec = exec_init()))
			free_and_exit(ERRNO);
		newlst = exec_fill(g_data->exec);
		free_tokens(&(g_data->lst));
		g_data->lst = newlst;
		if (g_data->exec)
		{
			ft_processor(g_data->exec);
			free_exec(g_data->exec);//
			g_data->exec = NULL;//
		}
	}
	parse_input(0);
}

void	parse_line(char **line, int last_char)
{
	int q_closed;

	q_closed = get_tokens(*line, last_char);
	free_and_null(line);
	//print_list(g_data->lst);//
	validate_tokens(q_closed);
	correct_tokens();
	//print_list(g_data->lst);//
	analise_tokens();
}

void	parse_input(char unfinished)
{
	int		ret;
	char	*line;

	//line = ft_strdup("\\");//
	if (!unfinished)
		write(1, "minishell", 9);
	write(1, "> ", 2);
	if ((ret = get_next_line(&line)) != 0)
	{//printf("gnl=%i\n", ret);//
		//printf("unfinished=%c\n", unfinished);//
		//if (!g_data->lst)
		//	unfinished = 0;
		parse_line(&line, unfinished);
		//printf("line parsed");
		return ;
	}
	if (ret == 0)
	{
		//printf("gnl=%i\n", ret);
		free_and_null(&line);
		write(1, "exit\n", 5);
		free_and_exit(0);
	}
}
