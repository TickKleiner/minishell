#include "../../include/lexer.h"

static void	del_last_token(t_dlist *last)
{
	if (last->prev)
		last->prev->next = NULL;
	if (((t_token *)(last->content))->str)
		free(((t_token *)(last->content))->str);
	free((t_token *)(last->content));
	free(last);
	last = NULL;
}

int			get_tokens(t_dlist **lst, char *line, int last_char)
{
	char	*tmp;
	t_dlist	*last;

	if (last_char == '\\' && !*line)
	{
		last = ft_dlstlast(*lst);
		if (!*(((t_token *)(last->content))->str + 1) && last->prev \
			&& ((t_token *)(last->prev->content))->len < 0 \
			&& *(((t_token *)(last->prev->content))->str) == '|')
		{
			del_last_token(last);
			free(line);
			parse_input('|', lst);
			return (1);
		}
		tmp = ((t_token *)(last->content))->str;
		((t_token *)(last->content))->str = \
					ft_substr(tmp, 0, ((t_token *)(last->content))->len - 1);
		free(tmp);
		if (!((t_token *)(last->content))->str)
			parser_exit(lst, &line);
		return (1);
	}
	return (split_line(lst, line, last_char));
}
//printf("len=%i\n", len);
	//printf("-%s\n", ((t_token *)((*lst)->content))->str);
	//printf("-%s\n", ((t_token *)((*lst)->next->content))->str);
