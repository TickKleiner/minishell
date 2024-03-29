/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corrected_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:12:29 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:14:58 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	process_tilde(char **new, int *start, int *end)
{
	t_env *env;

	env = find_env_b("HOME");
	if (env && env->value)
		*new = ft_strdup(env->value);
	else
		*new = ft_strdup(g_data->u_env->home);
	*start = (*end)--;
}

static int	paste_env(char *s, int *start, int *end, char **res)
{
	char *new;

	if (s[*start] == '$' && !ft_isalpha(s[*end]) && !ft_strchr("_?", s[*end]))
		*start = *end + 1;
	else
	{
		if (s[*start] == '~')
			process_tilde(&new, start, end);
		else if (s[*end] == '?')
		{
			new = ft_itoa(g_data->code);
			*start = *end + 1;
		}
		else
		{
			while (ft_isalpha(s[*end]) || \
					ft_isdigit(s[*end]) || s[*end] == '_')
				++(*end);
			new = find_env(ft_substr(s, *start + 1, *end - *start - 1));
			*start = (*end)--;
		}
		if (!stradd(res, new))
			return (0);
	}
	return (1);
}

static char	*substr_filtered(char *str, char *mask, int len, int end)
{
	char	*res;
	int		start;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	start = 0;
	while (start < end)
	{
		if (mask[start] == '1')
		{
			res[i] = str[start];
			++i;
		}
		++start;
	}
	res[i] = '\0';
	return (res);
}

static void	correct_str(t_token *token, char **res, char **mask)
{
	int		end;
	int		start;
	int		len;

	end = -1;
	start = 0;
	len = 0;
	while (++end <= token->len)
	{
		if ((*mask)[end] == '1')
			++len;
		else if (end == token->len && token->len == len)
			free_and_null(res);
		else if (ft_strchr("$~\0", (*mask)[end]))
		{
			if (len > 0)
				if (!stradd(res, substr_filtered(token->str + start, \
						*mask + start, len, end - start)))
					parser_exit(ERRNO, mask);
			if ((*mask)[start = end++] == '$' || (*mask)[start] == '~')
				if (!paste_env(token->str, &start, &end, res))
					parser_exit(ERRNO, mask);
		}
	}
}

char		*corrected_str(t_token *token)
{
	char *mask;
	char *res;

	if (!(mask = str_mask(token->str, token->len)))
		free_and_exit(ERRNO);
	if (!(res = ft_strdup("")))
		parser_exit(ERRNO, &mask);
	correct_str(token, &res, &mask);
	free(mask);
	if (res && !ft_strcmp(res, "\0") &&
		!(ft_strchr(token->str, '\'') || \
		ft_strchr(token->str, '\"')))
	{
		token->len = 0;
		free(res);
		res = NULL;
	}
	else
		token->len = 1;
	return (res);
}
