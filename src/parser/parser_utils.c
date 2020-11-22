/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:29 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 19:54:13 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

int		stradd(char **str, char *new)
{
	char *tmp;

	if (!new || !*str)
	{
		if (*str)
			free(*str);
		if (new)
			free(new);
		return (0);
	}
	tmp = *str;
	*str = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
	if (!*str)
		return (0);
	return (1);
}

void	print_list(t_dlist *lst)//for tests
{
	while (lst)
	{
		printf("[%s,", ((t_token *)(lst->content))->str);
		printf("%i]->", ((t_token *)(lst->content))->len);
		lst = (lst)->next;
	}
	printf("NULL\n");
}
