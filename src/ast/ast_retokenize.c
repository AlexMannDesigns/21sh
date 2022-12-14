/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_retokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:21:06 by amann             #+#    #+#             */
/*   Updated: 2022/11/11 16:55:39 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static const t_token_dispatch	*get_parse_token_dispatch(void)
{
	static const t_token_dispatch	dispatch_table[] = {
	{'$', TOKEN_DOLLAR},
	{'~', TOKEN_TILDE},
	{'"', TOKEN_DOUBLE_QUOTE},
	{'\'', TOKEN_SINGLE_QUOTE},
	{'{', TOKEN_CURLY_OPEN},
	{'}', TOKEN_CURLY_CLOSED},
	{'+', TOKEN_PLUS},
	{'-', TOKEN_MINUS},
	{':', TOKEN_COLON},
	{'/', TOKEN_FWD_SLASH},
	{'=', TOKEN_EQUALS},
	{'\0', TOKEN_NULL}
	};

	return (dispatch_table);
}

static t_token_type	get_parser_token_type(char value)
{
	const t_token_dispatch	*dispatch_table;
	size_t					i;

	dispatch_table = get_parse_token_dispatch();
	i = 0;
	while (dispatch_table[i].token != TOKEN_NULL)
	{
		if (dispatch_table[i].symbol == value)
			return (dispatch_table[i].token);
		i++;
	}
	if (ft_is_whitespace(value))
		return (TOKEN_WHITESPACE);
	return (TOKEN_WORD);
}

static t_tokenizer	retokenize_init(char *line)
{
	t_tokenizer	t;

	t.buff = ft_strnew(ft_strlen(line) + 1);
	t.buff_idx = 0;
	return (t);
}

static void	rt_loop(t_tokenizer *t, t_token **res, t_token_type *type, char *lc)
{
	token_add(res, *type, ft_strdup(t->buff));
	ft_bzero(t->buff, ft_strlen(t->buff) + 1);
	*type = get_parser_token_type(*lc);
	t->buff_idx = 0;
}

t_token	*ast_retokenize(char *line)
{
	t_token			*result;
	t_token_type	type;
	int				i;
	t_tokenizer		t;

	t = retokenize_init(line);
	if (!t.buff)
		return (NULL);
	result = NULL;
	type = get_parser_token_type(line[0]);
	i = 0;
	while (line[i])
	{
		if (get_parser_token_type(line[i]) != type
			|| (type & (TOKEN_DOUBLE_QUOTE | TOKEN_SINGLE_QUOTE) && i > 0))
			rt_loop(&t, &result, &type, line + i);
		t.buff[t.buff_idx] = line[i];
		(t.buff_idx)++;
		i++;
	}
	token_add(&result, type, ft_strdup(t.buff));
	free(t.buff);
	return (result);
}
